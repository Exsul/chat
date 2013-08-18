#include "../base.h"

enum MY_EVENTS
{
  CHAT_MESSAGE_EVENT
};

struct chat_client_module : public ed::module
{
  chat_client_module( ed::gateway &_gw ) : module("CHAT_CLIENT", _gw)
  {
    RegisterEvent(TOSTRING(CHAT_MESSAGE_EVENT), CHAT_MESSAGE_EVENT);

    ed::event_source_constructor es = GetSourceConstructor();
    es.event = CHAT_MESSAGE_EVENT;

    RegisterPostHandler(&chat_client_module::OnMessage, es);
  }

  void OnMessage( const ed::event_context<std::string> &a )
  {
    throw_assert(a.payload);
    std::cout << "<" << *a.payload << std::endl;
  }

  void SendMessage( const std::string &mes )
  {
    std::cout << ">" << mes << std::endl;
    SendEvent(CHAT_MESSAGE_EVENT, mes); 
  }


  ~chat_client_module()
  {
    UnregisterHandlers(this);
  }
};