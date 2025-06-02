#include <gtest/gtest.h>

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

#include "core/util/include/util.hpp"
#include "mpi/example/include/ops_mpi.hpp"

class NesterovATestTaskMPI : public ::testing::TestWithParam<double> {
 protected:
  void SetUp() override {
    std::ifstream test_file(ppc::util::GetAbsolutePath("mpi/example/data/test.txt"));
    ASSERT_TRUE(test_file.is_open()) << "Failed to open input file";
    std::string line;
    std::getline(test_file, line);
    test_file.close();
    base_count = std::stoi(line);
  }

  [[nodiscard]] size_t GetCount() const { return static_cast<size_t>(base_count * GetParam()); }

  int base_count = 0;
};

TEST_P(NesterovATestTaskMPI, MatmulFromFile) {
  const size_t count = GetCount();

  std::vector<int> in(count * count, 0);
  for (size_t i = 0; i < count; ++i) {
    in[(i * count) + i] = 1;
  }

  nesterov_a_test_task_mpi::TestTaskMPI test_task_mpi(in);
  ASSERT_TRUE(test_task_mpi.Validation());
  test_task_mpi.PreProcessing();
  test_task_mpi.Run();
  test_task_mpi.PostProcessing();

  EXPECT_EQ(in, test_task_mpi.Get());
}

TEST_P(NesterovATestTaskMPI, MultiplyRowMajorUtilTestFromFile) {
  const size_t count = GetCount();

  std::vector<int> in(count * count, 0);
  for (size_t i = 0; i < count; ++i) {
    in[(i * count) + i] = 1;
  }

  std::vector<int> out(count * count, 0);
  nesterov_a_test_task_mpi::MultiplyRowMajor(in, out, static_cast<int>(count));

  EXPECT_EQ(in, out);
}

TEST_P(NesterovATestTaskMPI, MultiplyColumnMajorUtilTestFromFile) {
  const size_t count = GetCount();

  std::vector<int> in(count * count, 0);
  for (size_t i = 0; i < count; ++i) {
    in[(i * count) + i] = 1;
  }

  std::vector<int> out(count * count, 0);
  nesterov_a_test_task_mpi::MultiplyColumnMajor(in, out, static_cast<int>(count));

  EXPECT_EQ(in, out);
}

INSTANTIATE_TEST_SUITE_P_NOLINT(FileMatrixTestsMPI, NesterovATestTaskMPI, ::testing::Values(0.5, 1.0));
