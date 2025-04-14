#include "mpi/example/include/ops_mpi.hpp"

#include <mpi.h>

#include <cmath>
#include <cstddef>
#include <vector>

bool nesterov_a_test_task_mpi::TestTaskMPI::PreProcessingImpl() {
  // Init value for input and output
  unsigned int input_size = task_data->inputs_count[0];
  auto *in_ptr = reinterpret_cast<int *>(task_data->inputs[0]);
  input_ = std::vector<int>(in_ptr, in_ptr + input_size);

  unsigned int output_size = task_data->outputs_count[0];
  output_ = std::vector<int>(output_size, 0);

  rc_size_ = static_cast<int>(std::sqrt(input_size));
  return true;
}

bool nesterov_a_test_task_mpi::TestTaskMPI::ValidationImpl() {
  // Check equality of counts elements
  return task_data->inputs_count[0] == task_data->outputs_count[0];
}

bool nesterov_a_test_task_mpi::TestTaskMPI::RunImpl() {
  MultiplyMatrixBasedOnRank();
  return true;
}

void nesterov_a_test_task_mpi::TestTaskMPI::MultiplyMatrixBasedOnRank() {
  int rank = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    MultiplyRowMajor();
  } else {
    MultiplyColumnMajor();
  }
  MPI_Barrier(MPI_COMM_WORLD);
}

void nesterov_a_test_task_mpi::TestTaskMPI::MultiplyRowMajor() {
  for (int i = 0; i < rc_size_; ++i) {
    for (int j = 0; j < rc_size_; ++j) {
      for (int k = 0; k < rc_size_; ++k) {
        output_[(i * rc_size_) + j] += input_[(i * rc_size_) + k] * input_[(k * rc_size_) + j];
      }
    }
  }
}

void nesterov_a_test_task_mpi::TestTaskMPI::MultiplyColumnMajor() {
  for (int j = 0; j < rc_size_; ++j) {
    for (int k = 0; k < rc_size_; ++k) {
      for (int i = 0; i < rc_size_; ++i) {
        output_[(i * rc_size_) + j] += input_[(i * rc_size_) + k] * input_[(k * rc_size_) + j];
      }
    }
  }
}

bool nesterov_a_test_task_mpi::TestTaskMPI::PostProcessingImpl() {
  for (size_t i = 0; i < output_.size(); i++) {
    reinterpret_cast<int *>(task_data->outputs[0])[i] = output_[i];
  }
  return true;
}
