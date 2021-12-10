#include "Acceptor.h"

using namespace std;

namespace MPOST
{
  void CreateAcceptor();
  int RunLoop();
  void AddEventListener(int eventType, void (*eventHandler)(CAcceptor *acceptor, int value));
}