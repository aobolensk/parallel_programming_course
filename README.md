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

1. Nesterov, A. (2021). *Automation of teaching practice processes using the parallel programming course
   as a case study* [in Russian] (original title: "Автоматизация процессов преподавания практики на
   примере курса по параллельному программированию"). In [*Russian Supercomputing Days*,
   pp. 52-61.](https://web.archive.org/web/20250416004721/https://russianscdays.org/files/2021/RuSCDays21_Proceedings.pdf#page=52)
1. Nesterov, A., Obolenskiy, A., Sysoyev, A., Meyerov, I. (2026). *Practical Aspects of Teaching Parallel
   Programming at the Lobachevsky University*. In V. Voevodin, A. Antonov, D. Nikitenko (Eds.),
   *Supercomputing* (RuSCDays 2025), Lecture Notes in Computer Science, vol. 16196, pp. 518-532.
   Springer. [DOI: 10.1007/978-3-032-13127-0_37](https://doi.org/10.1007/978-3-032-13127-0_37)
