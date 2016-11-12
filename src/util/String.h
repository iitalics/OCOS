#pragma once
#include "Slice.h"

using String = Slice<const char>;

template <size_t N>
inline String c_string (const char (&buffer)[N])
{
  if (buffer[N - 1] == '\0')
    return String(buffer, N - 1);
  else
    return String(buffer, N);
}
