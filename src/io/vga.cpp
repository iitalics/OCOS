#include "term.h"
#include <cstdint>
namespace io {

#define VGA_BUF ((uint16_t*) 0xb8000)


  VGA::VGA ()
    : row(0), col(0), style(style_of())
  {}

  void VGA::clear ()
  {
    for (int i = 0; i < (width() * height()); i++) {
      VGA_BUF[i] = 0;
    }
  }

  void VGA::set_style (Style s)
  {
    style = s;
  }

  void VGA::move_to (int x, int y)
  {
    row = x;
    col = y;
  }

  void VGA::write (char c)
  {
    uint16_t entry = c | (style << 8);
    switch (c) {
    case '\n':
      line_break();

    default:
      VGA_BUF[row * width() + col++] = entry;
      if (col >= width())
        line_break();
      break;
    }
  }

  void VGA::line_break ()
  {
    row++;
    col = 0;
    /* TODO: scroll? */
  }

}
