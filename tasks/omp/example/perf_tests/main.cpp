#include <gtest/gtest.h>

#include <chrono>
#include <cstddef>
#include <memory>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "core/util/include/util.hpp"
#include "omp/example/include/ops_omp.hpp"

class NesterovTaskOMPTest : public ::testing::TestWithParam<ppc::core::PerfResults::TypeOfRunning> {
 protected:
  static void RunTest(ppc::core::PerfResults::TypeOfRunning mode) {
    constexpr size_t kCount = 300;

    // Create data
    std::vector<int> in(kCount * kCount, 0);
    for (size_t i = 0; i < kCount; i++) {
      in[(i * kCount) + i] = 1;
    }

    // Create Task
    auto test_task_omp = std::make_shared<nesterov_a_test_task_omp::TestTaskOpenMP>(in);

    // Create Perf analyzer
    ppc::core::Perf perf_analyzer(test_task_omp);

    // Create Perf attributes
    ppc::core::PerfAttr perf_attr;
    const auto t0 = std::chrono::high_resolution_clock::now();
    perf_attr.current_timer = [&] {
      auto current_time_point = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
      return static_cast<double>(duration) * 1e-9;
    };

    if (mode == ppc::core::PerfResults::TypeOfRunning::kPipeline) {
      perf_analyzer.PipelineRun(perf_attr);
    } else {
      perf_analyzer.TaskRun(perf_attr);
    }

    perf_analyzer.PrintPerfStatistic();

    ASSERT_EQ(in, test_task_omp->Get());
  }
};

TEST_P(NesterovTaskOMPTest, RunModes) { RunTest(GetParam()); }

INSTANTIATE_TEST_SUITE_P_NOLINT(NesterovOMPTests, NesterovTaskOMPTest,
                                ::testing::Values(ppc::core::PerfResults::TypeOfRunning::kPipeline,
                                                  ppc::core::PerfResults::TypeOfRunning::kTaskRun));
