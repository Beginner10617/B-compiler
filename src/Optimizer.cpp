#include "Optimizer.h"

Optimizer::Optimizer(Compiler *c) { compiler = c; }

std::optinal<int> Optimizer::get_const(const Arg &arg) {
  const auto visitor = overloads {
    [&](const Literal &lit) -> std::optional<int> { return lit.literal; },
        [&](const Var &var) -> std::optional<int> {
          auto it = const_vars.find(var.index);
          if (it != const_vars.end())
            return it->second;
          return std::nullopt;
        },
        [&](const auto &) -> std::optional<int> { return std::nullopt; }
  }
}

void Optimizer::remove_const(const Var &arg) {
  auto it = const_vars.find(arg.index);
  if (it != const_vars.end())
    const_var.erase(arg.index);
}

void Optimizer::optimize() {}
