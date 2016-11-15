#pragma once
#include <cstdint>
#include <util/String.h>
namespace io {

  enum Color {
    Black = 0, Blue = 1, Green = 2, Cyan = 3,
    Red = 4, Magenta = 5, Brown = 6, LightGrey = 7,
    DarkGrey = 8, LightBlue = 9, LightGreen = 10, LightCyan = 11,
    LightRed = 12, LightMagenta = 13, LightBrown = 14, White = 15,
  };
  using Style = int;
  inline Style style_of (Color fg = White, Color bg = Black)
  {
    return (int) fg | (int) ((bg & 0x7) << 4);
  }

  /* VGA terminal output */
  struct VGA {
    enum { WIDTH = 80, HEIGHT = 25 };
    VGA ();
    inline int width () { return WIDTH; }
    inline int height () { return HEIGHT; }
    void clear ();
    void set_style (Style s);
    void move_to (int row, int col);

    void write (char c);
    void write (String s);
    void line_break ();
    void flush ();
    
  private:
    int row_, col_;
    uint16_t style_;
    bool invalid_;

    void scroll_line_ ();
    uint16_t scroll_;
  };

}
