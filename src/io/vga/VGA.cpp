#include "../term.h"
namespace io {
#define VGA_BUF ((volatile uint16_t*) 0xb8000)
  static uint16_t vga_back_buf[VGA::WIDTH * VGA::HEIGHT];

  VGA::VGA ()
    : row_(0), col_(0)
    , style_(style_of())
    , invalid_(true)
    , scroll_(0)
  {
    for (int i = 0; i < WIDTH * HEIGHT; i++)
      vga_back_buf[i] = 0;
  }

  void VGA::clear ()
  {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
      vga_back_buf[i] = 0;
      VGA_BUF[i] = 0;
    }
    scroll_ = 0;
    row_ = col_ = 0;
    invalid_ = false;
  }

  void VGA::set_style (Style s)
  {
    style_ = s;
  }

  void VGA::move_to (int y, int x)
  {
    row_ = y % HEIGHT;
    col_ = x % WIDTH;
  }

  void VGA::write (String s)
  {
    for (char c : s) write(c);
  }

  void VGA::write (char c)
  {
    uint16_t entry = c | (style_ << 8);
    switch (c) {
    case '\r':
      col_ = 0;
      break;
    case '\n':
      line_break();
      break;
    default:
      {
        int y = (row_ + scroll_) % HEIGHT;
        int x = col_++;
        vga_back_buf[y * WIDTH + x] = entry;
        if (col_ >= WIDTH)
          line_break();
        break;
      }
    }
  }

  void VGA::line_break ()
  {
    flush();
    col_ = 0;
    row_++;
    if (row_ >= HEIGHT) {
      row_ = HEIGHT - 1;
      scroll_line_();
    }
  }

  void VGA::flush ()
  {
    int y = (row_ + scroll_) % HEIGHT;
    for (int i = 0; i < WIDTH; i++)
      VGA_BUF[row_ * WIDTH + i] = vga_back_buf[y * WIDTH + i];
  }

  void VGA::scroll_line_ ()
  {
    scroll_ = (scroll_ + 1) % HEIGHT;

    int y0 = (scroll_ + row_) % HEIGHT;
    for (int i = 0; i < WIDTH; i++)
      vga_back_buf[y0 * WIDTH + i] = 0;
    
    for (int r = 0; r < HEIGHT; r++) {
      int y = (scroll_ + r) % HEIGHT;
      for (int i = 0; i < WIDTH; i++)
        VGA_BUF[r * WIDTH + i] = vga_back_buf[y * WIDTH + i];
    }
  }
}
