#include "term.h"
#include <cstdint>
namespace io {

#define VGA_BUF ((uint16_t*) 0xb8000)


  VGA::VGA ()
    : row_(0), col_(0)
    , style_(style_of())
  {}

  void VGA::clear ()
  {
    for (int i = 0; i < (width() * height()); i++) {
      VGA_BUF[i] = 0;
    }
  }

  void VGA::set_style (Style s)
  {
    style_ = s;
  }

  void VGA::move_to (int x, int y)
  {
    row_ = x;
    col_ = y;
  }

  void VGA::write (char c)
  {
    uint16_t entry = c | (style_ << 8);
    switch (c) {
    case '\n':
      line_break();

    default:
      VGA_BUF[row_ * width() + col_++] = entry;
      if (col_ >= width())
        line_break();
      break;
    }
  }

  void VGA::write (String s)
  {
    for (char c : s) write(c);
  }

  void VGA::line_break ()
  {
    row_++;
    col_ = 0;
    /* TODO: scroll? */
  }

}
