/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "AvgPoolLayer.h"

#include <cker/operation/AveragePool.h>

namespace onert
{
namespace backend
{
namespace cpu
{
namespace kernel
{

#define AVGPOOLING_PARAMETERS                            \
  nnfw::cker::PoolParams op_params;                      \
  op_params.stride_height = _strideHeight;               \
  op_params.stride_width = _strideWidth;                 \
  op_params.filter_height = _kernelHeight;               \
  op_params.filter_width = _kernelWidth;                 \
  op_params.padding_values.height = (int8_t)_paddingTop; \
  op_params.padding_values.width = (int8_t)_paddingLeft;

AvgPoolLayer::AvgPoolLayer()
    : _input(nullptr), _output(nullptr), _paddingLeft(0), _paddingTop(0), _paddingRight(0),
      _paddingBottom(0), _strideWidth(0), _strideHeight(0), _kernelWidth(0), _kernelHeight(0),
      _activation(ir::Activation::NONE)
{
  // DO NOTHING
}

void AvgPoolLayer::averagePoolFloat32()
{
  AVGPOOLING_PARAMETERS
  float output_activation_min, output_activation_max;
  CalculateActivationRangeFloat(_activation, &output_activation_min, &output_activation_max);
  op_params.float_activation_min = output_activation_min;
  op_params.float_activation_max = output_activation_max;

  nnfw::cker::AveragePool(op_params, convertTensorToCkerShape(_input),
                          reinterpret_cast<const float *>(_input->buffer()),
                          convertTensorToCkerShape(_output),
                          reinterpret_cast<float *>(_output->buffer()));
}
void AvgPoolLayer::averagePoolQuant8()
{
  AVGPOOLING_PARAMETERS
  int32_t output_activation_min = 0;
  int32_t output_activation_max = 0;
  CalculateActivationRangeUint8(_activation, _output, &output_activation_min,
                                &output_activation_max);
  op_params.quantized_activation_min = output_activation_min;
  op_params.quantized_activation_max = output_activation_max;

  nnfw::cker::AveragePool(op_params, convertTensorToCkerShape(_input),
                          reinterpret_cast<const uint8_t *>(_input->buffer()),
                          convertTensorToCkerShape(_output),
                          reinterpret_cast<uint8_t *>(_output->buffer()));
}

void AvgPoolLayer::configure(const operand::Tensor *input, const uint32_t paddingLeft,
                             const uint32_t paddingRight, const uint32_t paddingTop,
                             const uint32_t paddingBottom, const uint32_t strideWidth,
                             const uint32_t strideHeight, const uint32_t kernelWidth,
                             const uint32_t kernelHeight, const ir::Activation activation,
                             operand::Tensor *output)
{
  assert(input != nullptr);
  assert(output != nullptr);

  _input = input;
  _paddingLeft = paddingLeft;
  _paddingRight = paddingRight;
  _paddingTop = paddingTop;
  _paddingBottom = paddingBottom;
  _strideWidth = strideWidth;
  _strideHeight = strideHeight;
  _kernelWidth = kernelWidth;
  _kernelHeight = kernelHeight;
  _activation = activation;
  _output = output;
}

void AvgPoolLayer::run()
{
  if (_input->data_type() == OperandType::FLOAT32)
  {
    averagePoolFloat32();
  }
  else if (_input->data_type() == OperandType::QUANT8_ASYMM)
  {
    averagePoolQuant8();
  }
}

#undef AVGPOOLING_PARAMETERS

} // namespace kernel
} // namespace cpu
} // namespace backend
} // namespace onert
