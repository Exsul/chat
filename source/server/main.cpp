#include "server_module.h"
#include "../../ed/source/ed/communications/socket_connection.h"
#include "../../ed/source/ed/3party/win/utils.h"

void main()
{
  ed::com::socket_connection con("localhost", 3030);
  ed::gateway gw(con);
  chat_server_module module_exemplar(gw);

  while (true)
  {
    gw.Workflow();
    ed::Sleep(1);
  }
}