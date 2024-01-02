// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "core/include/task.hpp"
#include "reference/nearest_neighbor_elements/ref_task.hpp"

TEST(nearest_neighbor_elements, check_int32_t) {
  // Create data
  std::vector<int32_t> in(1256, 1);
  std::vector<int32_t> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (int i = 0; i < in.size(); i++) {
    in[i] = 2 * i;
  }
  in[234] = 0;
  in[235] = 1;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::NearestNeighborElements<int32_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_EQ(out[0], 0);
  EXPECT_EQ(out[1], 1);
  EXPECT_EQ(out_index[0], 234);
  EXPECT_EQ(out_index[1], 235);
}

TEST(nearest_neighbor_elements, check_validate_func) {
  // Create data
  std::vector<int32_t> in(125, 1);
  std::vector<int32_t> out(2, 0);
  std::vector<uint64_t> out_index(1, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::NearestNeighborElements<int32_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, false);
}

TEST(nearest_neighbor_elements, check_double) {
  // Create data
  std::vector<double> in(25680, 1);
  std::vector<double> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (int i = 0; i < in.size(); i++) {
    in[i] = 2 * i;
  }
  in[189] = 0.1;
  in[190] = 0.9;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::NearestNeighborElements<double, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_NEAR(out[0], 0.1, 1e-6);
  EXPECT_NEAR(out[1], 0.9, 1e-6);
  EXPECT_EQ(out_index[0], 189);
  EXPECT_EQ(out_index[1], 190);
}

TEST(nearest_neighbor_elements, check_int8_t) {
  // Create data
  std::vector<int8_t> in(250, -1);
  std::vector<int8_t> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (int i = 0; i < in.size(); i++) {
    if (i % 2 == 0) {
      in[i] = -50;
    } else {
      in[i] = 50;
    }
  }
  in[5] = 8;
  in[6] = -8;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::NearestNeighborElements<int8_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_EQ(out[0], 8);
  EXPECT_EQ(out[1], -8);
  EXPECT_EQ(out_index[0], 5);
  EXPECT_EQ(out_index[1], 6);
}

TEST(nearest_neighbor_elements, check_int64_t) {
  // Create data
  std::vector<int64_t> in(75836, 1);
  std::vector<int64_t> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (int i = 0; i < in.size(); i++) {
    if (i % 3 == 0) {
      in[i] = 10;
    }
    if (i % 3 == 1) {
      in[i] = 30;
    }
    if (i % 3 == 2) {
      in[i] = 70;
    }
  }
  in[20] = -100;
  in[21] = -119;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::NearestNeighborElements<int64_t, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_EQ(out[0], -100);
  EXPECT_EQ(out[1], -119);
  EXPECT_EQ(out_index[0], 20);
  EXPECT_EQ(out_index[1], 21);
}

TEST(nearest_neighbor_elements, check_float) {
  // Create data
  std::vector<float> in(20, 1);
  std::vector<float> out(2, 0);
  std::vector<uint64_t> out_index(2, 0);
  for (int i = 0; i < in.size(); i++) {
    in[i] += (i + 1.f) * 2.5f;
  }
  in[0] = 0.001;
  in[1] = 0.0025;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  taskData->inputs_count.emplace_back(in.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  taskData->outputs_count.emplace_back(out.size());
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t*>(out_index.data()));
  taskData->outputs_count.emplace_back(out_index.size());

  // Create Task
  ppc::reference::NearestNeighborElements<float, uint64_t> testTask(taskData);
  bool isValid = testTask.validation();
  EXPECT_EQ(isValid, true);
  testTask.pre_processing();
  testTask.run();
  testTask.post_processing();
  EXPECT_NEAR(out[0], 0.001, 1e-4);
  EXPECT_NEAR(out[1], 0.0025, 1e-4);
  EXPECT_EQ(out_index[0], 0);
  EXPECT_EQ(out_index[1], 1);
}
