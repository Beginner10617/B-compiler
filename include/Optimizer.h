#include <InterRepr.h>
#include <set>
#include <string>
#include <unordered_map>
class Optimizer {
public:
  Optimizer(Compiler *compiler);
  void optimize();
  void print_debug_data();

private:
  Compiler *compiler;
  std::unordered_map<size_t, big_int> const_vars;
  std::set<std::string> funcalls;
  std::optional<big_int> get_const(const Arg &arg);
  void remove_const(const Var &arg);
  void constant_folding(Func &func);
  struct Const_Folding_Visitor;
};
