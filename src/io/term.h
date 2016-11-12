#pragma once
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
    void clear ();
    void set_style (Style s);
    void write (char c);
    void move_to (int x, int y);
    void line_break ();
    inline int width () { return 80; }
    inline int height () { return 25; }

  private:
    int row_, col_, style_;
  };

}
