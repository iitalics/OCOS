#pragma once
#include "Slice.h"
namespace fmt {
  enum Mode {
    None=0,
    Any=1,
    EscapeDelim=2,
    
    DELIM='~',
    DELIM_Any='a',
    DELIM_Hex='x',
  };

  size_t find_format (const char* fmt, Mode& mode_out);

  template <typename Out>
  inline void format (Out& out, const char* fmt)
  {
    size_t i;
    for (i = 0; fmt[i]; i++) ;
    out.write(Slice<const char>(fmt, i));
  }
  
  template <typename Out, typename X, typename... Xs>
  inline void format (Out& out, const char* fmt, const X& arg, const Xs&... rest)
  {
    Mode mode = None;
    size_t i = find_format(fmt, mode);
    // pre-format
    if (i > 0)
      out.write(Slice<const char>(fmt, i));
    // format
    switch (mode) {
    case Any: // ~a
      writer(out, arg);
      break;
    case EscapeDelim: // ~~
      {
        out.write(Slice<const char>("~", 1));
        break;
      }
    case None: // ??
    default:
      break;
    }
    // post-format
    if (fmt[i])
      format(out, fmt + i + 2, rest...);
  }

  struct GenericOut
  {
    template <typename OutT>
    inline GenericOut (OutT& out)
      : out_((Any*) &out)
      , write_((AnyWrite) &OutT::write)
    {}

    void write (Slice<const char> s)
    {
      ((out_)->*(write_))(s);
    }

  private:
    struct Dummy {};
    using Any = Dummy;
    using AnyWrite = void (Any::*)(Slice<const char>);

    Any* out_;
    AnyWrite write_;
  };
};
