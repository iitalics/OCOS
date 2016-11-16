#include "mem.h"
extern "C" {
  extern char _kernel_begin, _kernel_end;
};
namespace mem {
  static Region validate_ram_region (unsigned long addr, unsigned long len)
  {
    /* regions in kernel code are not valid! */
    if (addr >= (unsigned long) &_kernel_begin
        && addr < (unsigned long) &_kernel_end) {
      /* adjust to latest page after kernel code */
      auto new_addr = (unsigned long) &_kernel_end;
      if (new_addr & 0xfffff)
        new_addr = (new_addr | 0xfffff) + 1;
      /* no bytes left? */
      if (new_addr > addr + len)
        len = 0;
      else
        len = (addr + len) - new_addr;
      addr = new_addr;
    }
    return Region((char*) addr, len);
  }

  /* RAM regions */
  const size_t max_ram_regions = 16;
  static size_t n_ram_regions = 0;
  static Region ram_regions[max_ram_regions];
  static size_t add_ram_region (unsigned long addr, unsigned long len)
  {
    /* validate */
    auto reg = validate_ram_region(addr, len);
    /* don't overflow the buffer */
    if (reg.len() > 0 && n_ram_regions < max_ram_regions) {
      ram_regions[n_ram_regions++] = reg;
      return 1;
    }
    else {
      return 0;
    }
  }
  Slice<Region> usable_ram_regions () {
    return Slice<Region>(ram_regions, n_ram_regions);
  }

  size_t find_ram_multiboot (multiboot_info_t &mbi)
  {
    using ulong = unsigned long;
    size_t count = 0;

    /* flag[6] => memory map available */
    if (mbi.flags & (1 << 6)) {
      ulong mmap = mbi.mmap_addr;
      while (mmap < mbi.mmap_addr + mbi.mmap_length) {
        /* read fields from multiboot struct */
        mmap += sizeof(ulong);
        ulong* fields = (ulong*) mmap;
        ulong size    = fields[-1];
        ulong base_lo = fields[0];
        ulong base_hi = fields[1];
        ulong len_lo  = fields[2];
        ulong len_hi  = fields[3];
        ulong type    = fields[4];
        mmap += size;

        if (base_hi == 0x00000000 // non-extended
            && len_hi == 0x00000000 // < 4Gb
            && type == 1 // non-reserved
            && base_lo > 0x0000ffff) {
          count += add_ram_region(base_lo, len_lo);
        }
      }
    }
    return count;
  }
};
