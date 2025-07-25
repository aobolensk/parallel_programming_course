from pathlib import Path
from collections import defaultdict
from datetime import datetime
import csv
import argparse
import subprocess
import yaml
import shutil
from jinja2 import Environment, FileSystemLoader
import logging

logging.basicConfig(level=logging.INFO, format="%(levelname)s: %(message)s")
logger = logging.getLogger(__name__)

task_types = ["all", "mpi", "omp", "seq", "stl", "tbb"]

script_dir = Path(__file__).parent
tasks_dir = script_dir.parent / "tasks"


def discover_tasks(tasks_dir, task_types):
    """Discover tasks and their implementation status from the filesystem."""
    directories = defaultdict(dict)

    if tasks_dir.exists() and tasks_dir.is_dir():
        for task_name_dir in tasks_dir.iterdir():
            if task_name_dir.is_dir() and task_name_dir.name not in ["common"]:
                task_name = task_name_dir.name
                for task_type in task_types:
                    task_type_dir = task_name_dir / task_type
                    if task_type_dir.exists() and task_type_dir.is_dir():
                        if task_name.endswith("_disabled"):
                            clean_task_name = task_name[: -len("_disabled")]
                            directories[clean_task_name][task_type] = "disabled"
                        else:
                            directories[task_name][task_type] = "done"

    return directories


directories = discover_tasks(tasks_dir, task_types)


def load_performance_data(perf_stat_file_path):
    """Load and parse performance statistics from CSV file."""

    perf_stats = dict()
    if perf_stat_file_path.exists():
        with open(perf_stat_file_path, "r", newline="") as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                task_name = row.get("Task")
                if task_name:
                    perf_stats[task_name] = {
                        "seq": row.get("SEQ", "?"),
                        "omp": row.get("OMP", "?"),
                        "tbb": row.get("TBB", "?"),
                        "stl": row.get("STL", "?"),
                        "all": row.get("ALL", "?"),
                        "mpi": "N/A",
                    }
    else:
        logger.warning("Performance stats CSV not found at %s", perf_stat_file_path)
    return perf_stats


def calculate_performance_metrics(perf_val, eff_num_proc, task_type):
    """Calculate acceleration and efficiency from performance value."""
    acceleration = "?"
    efficiency = "?"
    try:
        perf_float = float(perf_val)
        if perf_float > 0 and not (
            perf_float == float("inf") or perf_float != perf_float
        ):
            speedup = 1.0 / perf_float
            # For sequential code, acceleration and efficiency don't make sense
            # as it should be the baseline (speedup = 1.0 by definition)
            if task_type == "seq":
                acceleration = "1.00"  # Sequential is the baseline
                efficiency = "N/A"
            else:
                acceleration = f"{speedup:.2f}"
                efficiency = f"{speedup / eff_num_proc * 100:.2f}%"
    except (ValueError, TypeError):
        pass
    return acceleration, efficiency


def get_solution_points_and_style(task_type, status, cfg):
    """Get solution points and CSS style based on task type and status."""
    max_sol_points = int(cfg["scoreboard"]["task"][task_type]["solution"]["max"])
    sol_points = max_sol_points if status in ("done", "disabled") else 0
    solution_style = ""
    if status == "done":
        solution_style = "background-color: lightgreen;"
    elif status == "disabled":
        solution_style = "background-color: #6495ED;"
    return sol_points, solution_style


def check_plagiarism_and_calculate_penalty(
    dir, task_type, sol_points, plagiarism_cfg, cfg
):
    """Check if task is plagiarized and calculate penalty points."""
    clean_dir = dir[: -len("_disabled")] if dir.endswith("_disabled") else dir
    is_cheated = (
        dir in plagiarism_cfg["plagiarism"][task_type]
        or clean_dir in plagiarism_cfg["plagiarism"][task_type]
    )
    plagiarism_points = 0
    if is_cheated:
        plag_coeff = float(cfg["scoreboard"]["plagiarism"]["coefficient"])
        plagiarism_points = -plag_coeff * sol_points
    return is_cheated, plagiarism_points


def calculate_deadline_penalty(dir, task_type, status, deadlines_cfg, tasks_dir):
    """Calculate deadline penalty points based on git commit timestamp."""
    deadline_points = 0
    deadline_str = deadlines_cfg.get(task_type)
    if status == "done" and deadline_str:
        try:
            deadline_dt = datetime.fromisoformat(deadline_str)
            git_cmd = [
                "git",
                "log",
                "-1",
                "--format=%ct",
                str(
                    tasks_dir
                    / (dir + ("_disabled" if status == "disabled" else ""))
                    / task_type
                ),
            ]
            result = subprocess.run(git_cmd, capture_output=True, text=True)
            if result.stdout.strip().isdigit():
                commit_dt = datetime.fromtimestamp(int(result.stdout.strip()))
                days_late = (commit_dt - deadline_dt).days
                if days_late > 0:
                    deadline_points = -days_late
        except Exception:
            pass
    return deadline_points


def load_configurations():
    """Load all configuration files and return parsed data."""
    config_path = Path(__file__).parent / "data" / "threads-config.yml"
    assert config_path.exists(), f"Config file not found: {config_path}"
    with open(config_path, "r") as file:
        cfg = yaml.safe_load(file)
    assert cfg, "Configuration is empty"

    eff_num_proc = int(cfg["scoreboard"].get("efficiency", {}).get("num_proc", 1))
    deadlines_cfg = cfg["scoreboard"].get("deadlines", {})

    plagiarism_config_path = Path(__file__).parent / "data" / "plagiarism.yml"
    with open(plagiarism_config_path, "r") as file:
        plagiarism_cfg = yaml.safe_load(file)
    assert plagiarism_cfg, "Plagiarism configuration is empty"

    return cfg, eff_num_proc, deadlines_cfg, plagiarism_cfg


def main():
    """Main function to generate the scoreboard."""
    cfg, eff_num_proc, deadlines_cfg, plagiarism_cfg = load_configurations()

    env = Environment(loader=FileSystemLoader(Path(__file__).parent / "templates"))

    perf_stat_file_path = (
        script_dir.parent / "build" / "perf_stat_dir" / "task_run_perf_table.csv"
    )

    # Read and parse performance statistics CSV
    perf_stats = load_performance_data(perf_stat_file_path)

    rows = []
    for dir in sorted(directories.keys()):
        row_types = []
        total_count = 0
        for task_type in task_types:
            status = directories[dir].get(task_type)
            sol_points, solution_style = get_solution_points_and_style(
                task_type, status, cfg
            )

            task_points = sol_points
            is_cheated, plagiarism_points = check_plagiarism_and_calculate_penalty(
                dir, task_type, sol_points, plagiarism_cfg, cfg
            )
            task_points += plagiarism_points

            perf_val = perf_stats.get(dir, {}).get(task_type, "?")

            # Calculate acceleration and efficiency if performance data is available
            acceleration, efficiency = calculate_performance_metrics(
                perf_val, eff_num_proc, task_type
            )

            # Calculate deadline penalty points
            deadline_points = calculate_deadline_penalty(
                dir, task_type, status, deadlines_cfg, tasks_dir
            )

            row_types.append(
                {
                    "solution_points": sol_points,
                    "solution_style": solution_style,
                    "perf": perf_val,
                    "acceleration": acceleration,
                    "efficiency": efficiency,
                    "deadline_points": deadline_points,
                    "plagiarised": is_cheated,
                    "plagiarism_points": plagiarism_points,
                }
            )
            total_count += task_points

        rows.append({"task": dir, "types": row_types, "total": total_count})

    template = env.get_template("index.html.j2")
    html_content = template.render(task_types=task_types, rows=rows)

    parser = argparse.ArgumentParser(description="Generate HTML scoreboard.")
    parser.add_argument(
        "-o", "--output", type=str, required=True, help="Output file path"
    )
    args = parser.parse_args()

    output_path = Path(args.output)
    output_path.mkdir(parents=True, exist_ok=True)
    output_file = output_path / "index.html"
    with open(output_file, "w") as file:
        file.write(html_content)

    static_src = script_dir / "static"
    static_dst = output_path / "static"
    if static_src.exists():
        if static_dst.exists():
            shutil.rmtree(static_dst)
        shutil.copytree(static_src, static_dst)
        logger.info("Static directory copied to %s", static_dst)
    else:
        logger.warning("Static directory not found at %s", static_src)

    logger.info("HTML page generated at %s", output_file)


if __name__ == "__main__":
    main()
