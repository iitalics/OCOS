#pragma once
#include <boot/multiboot.h>
#include <util/Slice.h>
#include <cstdlib>

namespace mem {
  using Region = Slice<char>;
  Slice<Region> usable_ram_regions ();
  
  /* find usable RAM regions from multiboot info */
  size_t find_ram_multiboot (multiboot_info_t& mbi);
};

