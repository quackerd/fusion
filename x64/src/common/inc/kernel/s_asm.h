#ifndef _S_VMM_H_
#define _S_VMM_H_

#include "s_abi.h"
#include "s_type.h"

#define K_BASE_VADDR 0xFF
#define K_END_VADDR 0xFF

typedef struct
{
    // the kernel always reserves this much virtual space for HAL
    // this is mainly used for recursive page tables or other HAL actions
    k_virtual_addr_t reserved_vaddr_base;
    k_virtual_addr_t reserved_vaddr_end;

    // the k_vaddr_alignment determines the alignment of the kernel's address space
    // the reserved virtual address spaces above is also subject to the alignment
    uint64_t k_vaddr_alignment;
} k_hal_vmm_info;

// this function always returns the physical address of the new address space
// the function should identity refer to the virtual address K_BASE_VADDR to K_END_VADDR according to the current address space
// so that these pages are global (modifying the mapping in this area affects everyone)
// the K_BASE_VADDR to K_END_VADDR includes the reserved virtual addr space by the HAL
// if HAL's reserved virtual addr will be mapped to different physical pages, the HAL should make the change
k_physical_addr_t KAPI k_create_address_space(k_physical_addr_t addr_space,
                                              k_physical_page_alloc alloc);

// this function destroys the target address space without destroying the K_BASE_VADDR to K_END_VADDR
// target_addr_space is guaranteed to be not the same as the current address space
// when the function returns, the current address space must stay unchanged
void KAPI k_destroy_address_space(k_physical_addr_t target_addr_space,
                                  k_physical_page_free free);

// as the name implies
void KAPI k_switch_address_space(k_physical_addr_t target_addr_space);

// as the name implies
k_physical_addr_t KAPI k_get_current_address_space();

#endif