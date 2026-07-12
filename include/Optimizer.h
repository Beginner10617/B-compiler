#include <InterRepr.h>
#include <unordered_map>
class Optimizer {
public:
  Optimizer(Compiler *compiler);
  void optimize();
  int get_const(const Arg &arg);
  void remove_const(const Arg &arg);

private:
  Compiler *compiler;
  std::map<int, int> const_vars;
};
