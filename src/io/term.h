#pragma once
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
    return (int) fg | (int) (bg << 4);
  }

  /* VGA terminal output */
  struct VGA {
    VGA ();
    inline int width () { return 80; }
    inline int height () { return 25; }
    void clear ();
    void set_style (Style s);
    void move_to (int x, int y);

    void write (char c);
    void write (String s);
    void line_break ();

  private:
    int row_, col_, style_;
  };

}
