#include <InterRepr.h>
#include <set>
#include <string>
#include <unordered_map>
class Optimizer {
public:
  Optimizer(Compiler *compiler);
  void optimize();

private:
  Compiler *compiler;
  std::unordered_map<int, int> const_vars;
  std::set<std::string> funcalls;
  std::optional<int> get_const(const Arg &arg);
  void remove_const(const Var &arg);
  void optimize_function(Func &func);
};
