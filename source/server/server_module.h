#include "../base.h"

enum MY_EVENTS
{
  CHAT_MESSAGE_EVENT
};

struct chat_server_module : public ed::module
{
  chat_server_module( ed::gateway &_gw ) : module("CHAT_SERVER", _gw)
  {
    RegisterEvent(TOSTRING(CHAT_MESSAGE_EVENT), CHAT_MESSAGE_EVENT);

    ed::event_source es;
    es.event = CHAT_MESSAGE_EVENT;

    RegisterPostHandler(&chat_server_module::OnMessage, es);
  }

  void OnMessage( const ed::event_context<std::string> &a )
  {
    throw_assert(a.payload);
    std::cout << "RECV:" << *a.payload << std::endl;
    SendEvent(CHAT_MESSAGE_EVENT, *a.payload); 
  }

  ~chat_server_module()
  {
    UnregisterHandlers(this);
  }
};