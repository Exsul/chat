#include "../../ed/source/ed/kit/module.h"

struct chat_server_module : public ed::module
{
  chat_server_module( ed::gateway &_gw ) : module("CHAT_SERVER", _gw)
  {}
  ~chat_server_module()
  {
    UnregisterHandlers(this);
  }
};