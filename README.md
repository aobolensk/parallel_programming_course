# Parallel Programming Course

[![Build application](https://github.com/learning-process/parallel_programming_course/actions/workflows/main.yml/badge.svg?branch=master)](https://github.com/learning-process/parallel_programming_course/actions/workflows/main.yml)
[![Pages](https://github.com/learning-process/parallel_programming_course/actions/workflows/pages.yml/badge.svg?branch=master)](https://github.com/learning-process/parallel_programming_course/actions/workflows/pages.yml)
[![CodeQL](https://github.com/learning-process/parallel_programming_course/actions/workflows/codeql.yml/badge.svg?branch=master)](https://github.com/learning-process/parallel_programming_course/actions/workflows/codeql.yml)
[![codecov](https://codecov.io/gh/learning-process/parallel_programming_course/graph/badge.svg?token=qCOtqeFyIz)](https://codecov.io/gh/learning-process/parallel_programming_course)
[![OpenSSF Scorecard](https://api.scorecard.dev/projects/github.com/learning-process/parallel_programming_course/badge)](https://scorecard.dev/viewer/?uri=github.com/learning-process/parallel_programming_course)

Welcome to the Parallel Programming Course!

Resources:

- Documentation (full instructions and quick start):
  [English](https://learning-process.github.io/parallel_programming_course/en/),
  [Russian](https://learning-process.github.io/parallel_programming_course/ru/)
- [Parallel Programming Course Slides](https://learning-process.github.io/parallel_programming_slides/)
- [Course Scoreboard](https://learning-process.github.io/parallel_programming_course/scoreboard/)
- [Code Coverage Report](https://learning-process.github.io/parallel_programming_course/coverage/)

## Parallel programming technologies

The following parallel programming technologies are considered in practice:

- [Message Passing Interface (MPI)](https://www.mpi-forum.org/)
- [OpenMP (Open Multi-Processing)](https://www.openmp.org/)
- [oneAPI Threading Building Blocks (oneTBB)](https://github.com/oneapi-src/oneTBB)
- [Multithreading in C++ (`std::thread`)](https://en.cppreference.com/w/cpp/thread/thread)

## Rules for submissions

1. You are not supposed to trigger CI jobs by frequent updates of your pull request.
   First you should test you work locally with all the scripts (code style).
   - Respect others time and don't slow down the job queue
2. Carefully check if the program can hang.

## Related papers

Use these LaTeX citation keys in your text:

- `\cite{nesterov2021automation}`
- `\cite{nesterov2026practical}`

```bibtex
@inproceedings{nesterov2021automation,
  author    = {Nesterov, A.},
  title     = {Automation of teaching practice processes using the parallel programming course as a case study},
  booktitle = {Russian Supercomputing Days},
  year      = {2021},
  pages     = {52--61},
  note      = {In Russian},
  url       = {https://web.archive.org/web/20250416004721/https://russianscdays.org/files/2021/RuSCDays21_Proceedings.pdf#page=52}
}

@incollection{nesterov2026practical,
  author    = {Nesterov, A. and Obolenskiy, A. and Sysoyev, A. and Meyerov, I.},
  title     = {Practical Aspects of Teaching Parallel Programming at the Lobachevsky University},
  booktitle = {Supercomputing (RuSCDays 2025)},
  editor    = {Voevodin, V. and Antonov, A. and Nikitenko, D.},
  series    = {Lecture Notes in Computer Science},
  volume    = {16196},
  pages     = {518--532},
  year      = {2026},
  publisher = {Springer},
  doi       = {10.1007/978-3-032-13127-0_37},
  url       = {https://doi.org/10.1007/978-3-032-13127-0_37}
}
```
