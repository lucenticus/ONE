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

#ifndef __ONERT_BACKEND_CONTROLFLOW_KERNEL_PERMUTETENSORSLAYER_H__
#define __ONERT_BACKEND_CONTROLFLOW_KERNEL_PERMUTETENSORSLAYER_H__

#include <exec/IPermuteFunction.h>

namespace onert
{
namespace backend
{
namespace controlflow
{
namespace kernel
{

class PermuteTensorsLayer : public onert::exec::IPermuteFunction
{
public:
  PermuteTensorsLayer(const std::vector<std::shared_ptr<onert::backend::ITensor>> &src_tensors,
                      const std::vector<std::shared_ptr<onert::backend::ITensor>> &dst_tensors,
                      std::vector<size_t> ranks)
  {
    _src_tensors = src_tensors;
    _dst_tensors = dst_tensors;
    _ranks = ranks;
  }

  void optimize() override
  {
    // DO NOTHING
  }
};

} // namespace kernel
} // namespace controlflow
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_CONTROLFLOW_KERNEL_PERMUTETENSORSLAYER_H__
