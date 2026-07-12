#include <InterRepr.h>
#include <unordered_map>
class Optimizer {
public:
  Optimizer(Compiler *compiler);
  void optimize();
  std::optional<int> get_const(const Arg &arg);
  void remove_const(const Var &arg);

private:
  Compiler *compiler;
  std::map<int, int> const_vars;
};
