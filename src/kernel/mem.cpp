#include "mem.h"
namespace mem {
  /* RAM regions */
  const size_t max_ram_regions = 16;
  static size_t n_ram_regions = 0;
  static Region ram_regions[max_ram_regions];
  static size_t add_ram_region (unsigned long addr, unsigned long len)
  {
    if (n_ram_regions < max_ram_regions) {
      ram_regions[n_ram_regions++] = Region((char*) addr, len);
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

    if (mbi.flags & (1 << 6)) {
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
