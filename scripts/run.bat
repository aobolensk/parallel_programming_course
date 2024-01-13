@echo off

build\bin\core_func_tests.exe --gtest_also_run_disabled_tests --gtest_repeat=10 --gtest_recreate_environments_when_repeating || exit 1
build\bin\ref_func_tests.exe  --gtest_also_run_disabled_tests --gtest_repeat=10 --gtest_recreate_environments_when_repeating || exit 1

if "%CLANG_BUILD%" NEQ "1" "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 4 build\bin\mpi_func_tests.exe --gtest_repeat=10 || exit 1
if "%CLANG_BUILD%" NEQ "1" build\bin\mpi_func_tests.exe || exit 1
if "%CLANG_BUILD%" NEQ "1" build\bin\omp_func_tests.exe  --gtest_also_run_disabled_tests --gtest_repeat=10 --gtest_recreate_environments_when_repeating || exit 1
build\bin\seq_func_tests.exe  --gtest_also_run_disabled_tests --gtest_repeat=10 --gtest_recreate_environments_when_repeating || exit 1
build\bin\stl_func_tests.exe  --gtest_also_run_disabled_tests --gtest_repeat=10 --gtest_recreate_environments_when_repeating || exit 1
build\bin\tbb_func_tests.exe  --gtest_also_run_disabled_tests --gtest_repeat=10 --gtest_recreate_environments_when_repeating || exit 1
