#include <io/term.h>
#include <boot/boot.h>

extern "C" {
  void kernel_main (void)
  {
    io::VGA vga;
    
    vga.clear();
    for (int y = 0; y < 10; y++) {
      if (y % 2)
        vga.set_style(io::style_of(io::White, io::Black));
      else
        vga.set_style(io::style_of(io::LightGrey, io::Black));

      vga.move_to(y, y);
      vga.write("Hello world!");
      vga.line_break();
    }

    vga.move_to(11, 0);
    if (multiboot_info_ptr) {
      vga.write("found multiboot info");
    }
  }
};
