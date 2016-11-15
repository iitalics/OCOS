#pragma once
#include <cstdlib>

template <typename T>
struct Slice {
  using elem = T;
  using iterator = T*;

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
  
  inline T* data () const { return data_; }
  inline size_t len () const { return len_; }

  inline T& operator[] (size_t i) { return data_[i]; }
  inline const T& operator[] (size_t i) const { return data_[i]; }

  inline T* begin () { return data_; }
  inline T* end () { return data_ + len_; }
  inline const T* begin () const { return data_; }
  inline const T* end () const { return data_ + len_; }
  
  inline operator Slice<const T> () const
  {
    return Slice<const T>(data_, len_);
  }
  
private:
  T* data_;
  size_t len_;
};
