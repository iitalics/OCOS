#include <io/term.h>
#include <boot/boot.h>
#include <util/fmt_prim.h>
#include <util/fmt.h>

/* fmt::hex() is having issues with unsigned ints */
static void hex_addr (io::VGA& vga, ulong addr)
{
  char buf[8];
  for (int i = 0; i < 8; i++) {
    buf[7 - i] = "0123456789abcdef"[addr & 0xf];
    addr = addr >> 4;
  }
  vga.write(String(buf, 8));
}

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
                "  mem-lower: ~a kB  mem-upper: ~a kB\n",
                fmt::bin(mbi.flags),
                fmt::pad(6, mbi.mem_lower),
                fmt::pad(6, mbi.mem_upper));

    using ulong = unsigned long;
    ulong mmap = mbi.mmap_addr;

    while (mmap < mbi.mmap_addr + mbi.mmap_length) {
      /* thanks, multiboot standard :] */
      mmap += sizeof(ulong);
      ulong* fields = (ulong*) mmap;
      ulong size    = fields[-1];
      ulong base_lo = fields[0];
      ulong base_hi = fields[1];
      ulong len_lo  = fields[2];
      ulong len_hi  = fields[3];
      ulong type    = fields[4];
      mmap += size;

      if (type == 1)
        vga.set_style(io::style_of(io::LightCyan));
      else
        vga.set_style(io::style_of(io::DarkGrey));

      fmt::format(vga,
                  "entry type: ~a ~a\n"
                  "     length: ~a kB\n"
                  "  base addr: ",
                  type,
                  type == 1 ? string("(usable)") : string("**reserved**"),
                  len_lo >> 10);
      hex_addr(vga, base_hi);
      vga.write(' ');
      hex_addr(vga, base_lo);
      vga.line_break();
    }
  }
};
