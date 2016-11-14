#include "fmt.h"
namespace fmt {
  size_t find_format (const char* fmt, Mode& mode_out)
  {
    size_t i;
    for (i = 0; fmt[i]; i++) {
      if (fmt[i] != DELIM)
        continue;

      if (fmt[i+1] == DELIM_Any) {
        mode_out = Any;
        break;
      }

      if (fmt[i+1] == DELIM) {
        mode_out = EscapeDelim;
        break;
      }
    }
    return i;
  }

  namespace conv {
    size_t from_int (char* tmp, long long x, long base)
    {
      size_t n = 0;
      char* ptr = tmp;

      if (x < 0) {
        x = -x;
        *(ptr++) = '-';
        n++;
      }

      long long y = x;
      do {
        ptr++;
        y /= base;
      } while (y != 0);

      do {
        *(--ptr) = "0123456789abcdef"[x % base];
        n++;
        x /= base;
      } while (x != 0);

      return n;
    }
  }
};

