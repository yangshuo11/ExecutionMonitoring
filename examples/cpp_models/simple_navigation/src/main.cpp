#include <despot/simple_tui.h>
#include "simple_navigation.h"

using namespace despot;

class TUI: public SimpleTUI {
public:
  TUI() {
  }

  DSPOMDP* InitializeModel(option::Option* options) {
    DSPOMDP* model = new SimpleNavigation();
    return model;
  }

  void InitializeDefaultParameters() {
  }
};

int main(int argc, char* argv[]) {
  return TUI().run(argc, argv);
}
