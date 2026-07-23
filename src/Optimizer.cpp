#include "Optimizer.h"
// TODO : populate const_vars, using BinOp of type "assignment"
// analyze ir to understand how assignment BinOp works
//
Optimizer::Optimizer(Compiler *c) {
  compiler = c;
  for (auto func : compiler->functions)
    func_control_flows.emplace(func.function_name, CFG(func));
}

CFG::CFG(Func &func) {
  blocks_ = {};
  size_t id = 0, st = 0, index = 0;
  // 1. Broadly divide BasicBlock(s), don't define edges yet
  // 2. Make a Label -> BasicBlock map (with 1)
  // 3. Run another loop to link all edges of the graph
  for (auto op : func.function_body) {
  }
}
