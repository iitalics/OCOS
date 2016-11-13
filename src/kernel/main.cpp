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
      vga.write(c_string("no multiboot info!"));
      return;
    }

    multiboot_info_t& mbi = *multiboot_info_ptr;
    fmt::format(vga,
                "multiboot info:\n"
                "  mem-lower:   0x~a\n"
                "  mem-upper:   0x~a\n"
                "  mmap-length: ~a\n"
                "  mmap-addr:   0x~a\n",
                fmt::Hex(mbi.mem_lower), fmt::Hex(mbi.mem_upper),
                mbi.mmap_length, fmt::Hex(mbi.mmap_addr));
  }
};
