#include <io/term.h>
#include <boot/boot.h>
#include <util/fmt_prim.h>
#include <util/fmt.h>

extern "C" {
  void kernel_main (void)
  {
    io::VGA vga;
    vga.clear();

    if (multiboot_info_ptr == nullptr) {
      vga.set_style(io::style_of(io::Black, io::Red));
      vga.write(string("no multiboot info!"));
      return;
    }

    multiboot_info_t& mbi = *multiboot_info_ptr;
    fmt::format(vga,
                "multiboot info:\n"
                "  flags:     ~a\n"
                "  mem-lower: ~a KB\n"
                "  mem-upper: ~a KB\n",
                fmt::pad(12, fmt::bin(mbi.flags)),
                fmt::pad(12, mbi.mem_lower),
                fmt::pad(12, mbi.mem_upper));
  }
};
