#include "Optimizer.h"

Optimizer::Optimizer(Compiler *c) { compiler = c; }

std::optional<int> Optimizer::get_const(const Arg &arg) {
  const auto visitor = overload{
      [&](const Literal &lit) -> std::optional<int> { return lit.literal; },
      [&](const Var &var) -> std::optional<int> {
        auto it = const_vars.find(var.index);
        if (it != const_vars.end())
          return it->second;
        return std::nullopt;
      },
      [&](const auto &) -> std::optional<int> { return std::nullopt; }};
  return std::visit(visitor, arg);
}

void Optimizer::remove_const(const Var &arg) {
  auto it = const_vars.find(arg.index);
  if (it != const_vars.end())
    const_vars.erase(arg.index);
}

void Optimizer::optimize() {
  for (auto func : compiler->functions)
    optimize_function(func);
  /*
  for (auto it = compiler->extrns.begin(); it != compiler->extrns.end();) {
    if (!funcalls.count(func_names))
      it = compiler->extrns.erase(it);
    else
      it++;
  }
  REMOVE UN-USED EXTERNS
  */
}

void Optimizer::optimize_function(Func &func) {
  for (Op operation : func.function_body) {
  }
}
