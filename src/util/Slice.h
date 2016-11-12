#pragma once
#include <cstdlib>

template <typename T>
struct Slice {
  inline Slice ()
    : data_(nullptr)
    , len_(0)
  {}

  inline Slice (T* data, size_t n)
    : data_(data)
    , len_(n)
  {}

  template <size_t N>
  inline Slice (T (&buffer)[N])
    : data_(buffer)
    , len_(N)
  {}
  
  T* data () const { return data_; }
  size_t len () const { return len_; }

  T& operator[] (size_t i) { return data_[i]; }
  const T& operator[] (size_t i) const { return data_[i]; }

  T* begin () { return data_; }
  T* end () { return data_ + len_; }
  const T* begin () const { return data_; }
  const T* end () const { return data_ + len_; }
  
  operator Slice<const T> () const
  {
    return Slice<const T>(data_, len_);
  }
  
private:
  T* data_;
  size_t len_;
};

using String = Slice<const char>;
