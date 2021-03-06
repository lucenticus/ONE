/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "luci/Import/Nodes/CircleGreater.h"

#include <luci/IR/Nodes/CircleGreater.h>

#include <loco.h>

namespace luci
{

bool CircleGreaterGraphBuilder::validate(const ValidateArgs &args) const
{
  const auto &inputs = args.op.inputs;
  const auto &outputs = args.op.outputs;

  if (inputs.size() != 2)
    return false;

  if (outputs.size() != 1)
    return false;

  const auto &tensors = args.reader.tensors();

  if (tensors[inputs[0]]->type != tensors[inputs[1]]->type)
    return false;

  if (tensors[outputs[0]]->type != circle::TensorType_BOOL)
    return false;

  return true;
}

CircleNode *CircleGreaterGraphBuilder::build_node(const circle::OperatorT &,
                                                  const std::vector<CircleNode *> &inputs,
                                                  loco::Graph *graph) const
{
  auto *node = graph->nodes()->create<CircleGreater>();
  node->x(inputs[0]);
  node->y(inputs[1]);

  return node;
}

} // namespace luci
