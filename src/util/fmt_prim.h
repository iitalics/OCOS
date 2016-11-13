#pragma once
namespace fmt {
  size_t int_to_str (char* tmp, long x, long base);
  
  template <typename Out>
  void writer (Out& out, long x)
  {
    char tmp[24];
    size_t len = int_to_str(tmp, x, 10);
    out.write(Slice<const char>(tmp, len));
  }

  struct Hex
  {
    long value;
    explicit Hex (long v)
      : value(v) {}
  };
  struct Bin
  {
    long value;
    explicit Bin (long v)
      : value(v) {}
  };
  
  template <typename Out>
  void writer (Out& out, Hex x)
  {
    char tmp[24];
    size_t len = int_to_str(tmp, x.value, 16);
    out.write(Slice<const char>(tmp, len));
  }
  template <typename Out>
  void writer (Out& out, Bin x)
  {
    char tmp[24];
    size_t len = int_to_str(tmp, x.value, 2);
    out.write(Slice<const char>(tmp, len));
  }

  template <typename Out>
  void writer (Out& out, Slice<const char> str)
  { out.write(str); }

  template <typename Out, typename T>
  void writer (Out& out, T* ptr)
  {
    writer(out, Hex((long) ptr));
  }
};
