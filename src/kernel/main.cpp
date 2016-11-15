#include <io/term.h>
#include <boot/boot.h>
#include <kernel/mem.h>
#include <util/fmt_prim.h>
#include <util/fmt.h>

extern "C" {  
  void kernel_main (void)
  {
    io::VGA vga;
    vga.clear();

    if (multiboot_info_ptr != nullptr) {
      mem::find_ram_multiboot(*multiboot_info_ptr);
    }

    auto ram = mem::usable_ram_regions();
    fmt::format(vga, "found ~a region(s) of usable RAM:\n",
                ram.len());

    for (auto region : ram) {
      fmt::format(vga, "  ~a: ~a kB\n",
                  region.data(),
                  region.len() >> 10);
    }
  }
};
