/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SquaredDiffLayer.h"

#include "OperationUtils.h"

#include <cker/operation/SqDiff.h>

namespace onert
{
namespace backend
{
namespace cpu
{
namespace kernel
{

SqDiffLayer::SqDiffLayer() : _input1(nullptr), _input2(nullptr), _output(nullptr)
{
  // DO NOTHING
}

void SqDiffLayer::SqDiffFloat32()
{
  nnfw::cker::SqDiff(
      convertTensorToCkerShape(_input1), reinterpret_cast<const float *>(_input1->buffer()),
      convertTensorToCkerShape(_input2), reinterpret_cast<const float *>(_input2->buffer()),
      convertTensorToCkerShape(_output), reinterpret_cast<float *>(_output->buffer()));
}

void SqDiffLayer::configure(const operand::Tensor *input1, const operand::Tensor *input2,
                            operand::Tensor *output)
{
  _input1 = input1;
  _input2 = input2;
  _output = output;
}

void SqDiffLayer::run()
{
  if (_input1->data_type() == OperandType::FLOAT32)
  {
    SqDiffFloat32();
  }
}
} // namespace kernel
} // namespace cpu
} // namespace backend
} // namespace onert
