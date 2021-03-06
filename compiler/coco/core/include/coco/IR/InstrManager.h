/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __COCO_IR_INSTR_MANAGER_H__
#define __COCO_IR_INSTR_MANAGER_H__

#include "coco/IR/Instr.h"
#include "coco/IR/Instrs.h"

#include "coco/IR/Op.forward.h"

#include "coco/IR/Bag.h"

#include "coco/IR/Object.forward.h"

#include "coco/IR/EntityBuilder.h"

#include "coco/ADT/PtrManager.h"

namespace coco
{

class InstrManager final : public PtrManager<Instr>, public EntityBuilder
{
public:
  InstrManager(Module *m = nullptr) { module(m); }

public:
  template <typename Ins> Ins *create(void);

public:
  /**
   * @brief Destroy (= deallocate) an Instr instance
   *
   * NOTE destroy(ins) WILL NOT update ins->parent(). An Instruction SHOULD BE detacted from a
   *      module before destroy call
   */
  void destroy(Instr *);
};

//
// Every instruction class SHOULD be default constructible
//
template <typename Ins> Ins *InstrManager::create(void)
{
  auto ins = new Ins;
  modulize(ins);
  return take(std::unique_ptr<Ins>(ins));
}

} // namespace coco

#endif // __COCO_IR_INSTR_MANAGER_H__
