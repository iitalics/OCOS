#include <io/term.h>
#include <boot/boot.h>
#include <kernel/mem.h>
#include <util/fmt_prim.h>
#include <util/fmt.h>

extern "C" {
  extern char _kernel_begin, _kernel_end;

  void kernel_main (void)
  {
    io::VGA vga;
    vga.clear();

    auto k_begin = &_kernel_begin;
    auto k_end = &_kernel_end;
    unsigned long k_size = (unsigned long) k_end - (unsigned long) k_begin;
    fmt::format(vga,
                "located kernel:\n"
                "~a - ~a  (~a bytes)\n"
                "kernel_main()  @  ~a\n"
                "sp  @  ~a\n",
                k_begin, k_end, k_size,
                kernel_main,
                &vga);

    if (multiboot_info_ptr != nullptr) {
      mem::find_ram_multiboot(*multiboot_info_ptr);
    }

    auto ram = mem::usable_ram_regions();
    fmt::format(vga, "found ~a region(s) of usable RAM:\n",
                ram.len());

    for (auto region : ram) {
      fmt::format(vga, "  ~a: ~a kB / ~a mB\n",
                  region.data(),
                  region.len() >> 10,
                  region.len() >> 20);
    }

    vga.line_break();
    vga.line_break();
  }
};
