#include "../ed/source/ed/kit/module.h"

#include <string>
#include <iostream>

template<>
std::string convert( const ed::event_data &a )
{
  if (!a.origin.PayloadSize())
    return "";
  const ed::buffer buf = a.origin;
  return buf;
}