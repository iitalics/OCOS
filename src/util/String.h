#pragma once
#include "Slice.h"

using MutString = Slice<char>;
using String = Slice<const char>;

template <typename T, size_t N>
inline Slice<T> string (T (&buffer)[N])
{
  if (buffer[N - 1] == '\0')
    return Slice<T>(buffer, N - 1);
  else
    return Slice<T>(buffer, N);
}

template <typename T>
inline Slice<T> c_string (T* buffer)
{
  for (int i = 0; ; i++) {
    if (buffer[i] == '\0')
      return Slice<T>(buffer, i);
  }
}
