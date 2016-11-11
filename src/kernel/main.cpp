#include <io/term.h>

int foo () {
}

extern "C" {
  void kernel_main (void)
  {
    io::VGA vga;
    const char* const msg = "Hello, world!";
    
    vga.clear();
    for (int y = 0; y < 10; y++) {
      if (y % 2)
        vga.set_style(io::style_of(io::White, io::Black));
      else
        vga.set_style(io::style_of(io::LightGrey, io::Black));

      for (int i = 0; msg[i]; i++)
        vga.write(msg[i]);
      vga.line_break();
    }
  }
};
