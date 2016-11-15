#pragma once
#include "Slice.h"
#include <cstdlib>
namespace fmt {
  namespace conv {
    size_t from_int (char* buf, long long x, long base);
  };

  template <typename Out>
  void writer (Out& out, Slice<const char> str)
  { out.write(str); }

  template <typename Out, typename T>
  void writer (Out& out, T* ptr)
  {
    char tmp[10] = "0x";
    unsigned long ul = (unsigned long) ptr;
    for (int i = 0; i < 8; i++) {
      tmp[10 - 1 - i] = "0123456789abcdef"[ul & 0xf];
      ul = ul >> 4;
    }
    out.write(Slice<const char>(tmp, 10));
  }

  template <typename T>
  struct HexI {
    T value;
    explicit HexI (T v) : value(v) {}
  };
  template <typename T>
  struct BinI {
    T value;
    explicit BinI (T v) : value(v) {}
  };
  
  template <typename T>
  inline HexI<T> hex (T x) { return HexI<T>(x); }
  template <typename T>
  inline BinI<T> bin (T x) { return BinI<T>(x); }

  template <typename Out>
  void writer (Out& out, long long ll)
  {
    char tmp[32];
    out.write(Slice<char>(tmp, conv::from_int(tmp, ll, 10)));
  }
  template <typename Out, typename T>
  void writer (Out& out, HexI<T> x)
  {
    char tmp[32];
    out.write(Slice<char>(tmp, conv::from_int(tmp, x.value, 16)));
  }
  template <typename Out, typename T>
  void writer (Out& out, BinI<T> x)
  {
    char tmp[66];
    out.write(Slice<char>(tmp, conv::from_int(tmp, x.value, 2)));
  }

  template <typename X>
  struct Pad {
    const X& val;
    int num;
    char pad_char;
    Pad (int n, char pc, const X& v)
      : val(v), num(n), pad_char(pc) {}
  };
  template <typename Out, typename X>
  struct PadOut {
    Out& out;
    const Pad<X>& pad;
    explicit PadOut (Out& o, const Pad<X>& p)
      : out(o), pad(p) {}
    void write (Slice<const char> s)
    {
      int pad_count = pad.num - s.len();
      if (pad_count > 0) {
        char pads[pad_count];
        for (int i = 0; i < pad_count; i++)
          pads[i] = pad.pad_char;
        out.write(Slice<char>(pads, pad_count));
      }
      out.write(s);
    }
  };

  template <typename T>
  inline Pad<T> pad (int n, const T& x) { return Pad<T>(n, ' ', x); }
  template <typename T>
  inline Pad<T> pad (int n, char sp, const T& x) { return Pad<T>(n, sp, x); }
  
  template <typename Out, typename X>
  void writer (Out& out, const Pad<X>& p) {
    PadOut<Out,X> pad_out(out, p);
    writer(pad_out, p.val);
  }
};
