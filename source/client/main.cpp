#include "client_module.h"
#include "../../ed/source/ed/communications/socket_connection.h"
#include "../../ed/source/ed/3party/win/utils.h"

struct data
{
  char *buffer;
  std::size_t size;
};

struct read_timeouted
{
};

#include <windows.h>

DWORD WINAPI get_input ( LPVOID arg )
{
  data *buf = (data*)arg;
  return !std::cin.getline ( buf->buffer, buf->size );
}

std::string GetAsyncString()
{
  static char buffer[256] = {0};
  static data arg = {buffer, 256};
  static HANDLE h = 0;
  static DWORD id;

  if (!h)
    h = CreateThread ( NULL, 0, get_input, &arg, 0, &id );
  if (WaitForSingleObjectEx ( h, 100, FALSE ) == WAIT_TIMEOUT)
    throw read_timeouted();
  CloseHandle(h);
  h = 0;
  return buffer;
}

#undef SendMessage

void main()
{
  ed::com::socket_connection con("localhost", 3030);
  ed::gateway gw(con);
  chat_client_module module_exemplar(gw);


  while (true)
  {
    gw.Workflow();
    try
    {
      module_exemplar.SendMessage(GetAsyncString());
    } catch (read_timeouted &)
    {
    }
  }
}