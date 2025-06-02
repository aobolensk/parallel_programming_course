#pragma once

#include <vector>

#include "core/task/include/task.hpp"

namespace nesterov_a_test_task_tbb {

class TestTaskTBB : public ppc::core::Task {
 public:
  explicit TestTaskTBB(const std::vector<int>& in) : input_(in) {}
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
  std::vector<int> Get();

 private:
  std::vector<int> input_, output_;
  int rc_size_{};
};

}  // namespace nesterov_a_test_task_tbb
