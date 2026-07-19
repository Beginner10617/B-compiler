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
    constant_folding(func);
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

struct Const_Folding_Visitor {
  Ops &new_ops;

  void operator()(UnOp un_op) {
    // placeholder for now
    new_ops.push_back(un_op);
  }

  void operator()(BinOp bin_op) {
    // placeholder for now
    new_ops.push_back(bin_op);
  }

  void operator()(Funcall fun_call) {
    // placeholder for now
    new_ops.push_back(fun_call);
  }

  void operator()(DataSection data_sec) {
    // placeholder for now
    new_ops.push_back(data_sec);
  }

  void operator()(ReturnValue ret_val) {
    // placeholder for now
    new_ops.push_back(ret_val);
  }

  void operator()(JmpIfZero jz) {
    // placeholder for now
    new_ops.push_back(jz);
  }

  void operator()(Jmp jmp) {
    // placeholder for now
    new_ops.push_back(jmp);
  }

  void operator()(Label label) {
    // placeholder for now
    new_ops.push_back(label);
  }

  void operator()(Store store) {
    // placeholder for now
    new_ops.push_back(store);
  }

  void operator()(Asm _asm) {
    // placeholder for now
    new_ops.push_back(_asm);
  }
};

void Optimizer::constant_folding(Func &func) {
  Ops new_ops;
  for (Op operation : func.function_body) {
    std::visit(Const_Folding_Visitor{new_ops}, operation);
  }
  func.function_body = new_ops;
}
