#include "Optimizer.h"
// TODO : populate const_vars, using BinOp of type "assignment"
// analyze ir to understand how assignment BinOp works
//
Optimizer::Optimizer(Compiler *c) { compiler = c; }

void Optimizer::print_debug_data() {
  std::cout << "Constant table:\n";
  for (auto const_pair : const_vars) {
    std::cout << "Var(" << const_pair.first << ") : " << const_pair.second
              << "\n";
  }
}

std::optional<big_int> Optimizer::get_const(const Arg &arg) {
  const auto visitor = overload{
      [&](const Literal &lit) -> std::optional<big_int> { return lit.literal; },
      [&](const Var &var) -> std::optional<big_int> {
        auto it = const_vars.find(var.index);
        if (it != const_vars.end())
          return it->second;
        return std::nullopt;
      },
      [&](const NoArg *no_arg) -> std::optional<big_int> { return 0; },
      [&](const auto &) -> std::optional<big_int> { return std::nullopt; }};
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

struct Optimizer::Const_Folding_Visitor {
  Optimizer &opt;
  Ops &new_ops;

  void operator()(UnOp un_op) {
    // placeholder for now
    new_ops.push_back(un_op);
  }

  void operator()(BinOp bin_op) {
    // placeholder for now
    auto lval = opt.get_const(bin_op.lhs);
    auto rval = opt.get_const(bin_op.rhs);
    if ((!lval.has_value() || !rval.has_value()) &&
        bin_op.type != Tokentype::assignment) {
      new_ops.push_back(bin_op);
      return;
    }
    if (bin_op.type == Tokentype::assignment && !rval.has_value()) {
      new_ops.push_back(bin_op);
      return;
    }
    switch (bin_op.type) {
    case Tokentype::assignment:
      new_ops.push_back(BinOp{.var = bin_op.var,
                              .lhs = bin_op.lhs,
                              .rhs = Literal{rval.value()},
                              .type = bin_op.type});
      opt.const_vars[bin_op.var.index] = rval.value();
      break;
    case Tokentype::add:
      break;
    case Tokentype::sub:
      break;
    case Tokentype::mult:
      break;
    case Tokentype::divi:
      break;
    case Tokentype::bit_or:
      break;
    case Tokentype::bit_and:
      break;
    case Tokentype::bit_not:
      break;
    case Tokentype::shift_left:
      break;
    case Tokentype::shift_right:
      break;
    default:
      new_ops.push_back(bin_op);
    }
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
    std::visit(Const_Folding_Visitor{*this, new_ops}, operation);
  }
  func.function_body = new_ops;
}
