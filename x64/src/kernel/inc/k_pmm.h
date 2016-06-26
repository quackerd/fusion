#ifndef _K_PMM_H_
#define _K_PMM_H_

#include "avl_tree.h"
#include "linked_list.h"
#include "g_abi.h"
#include "s_pmm.h"
#include "k_atomic.h"

#define PMM_STATUS_SUCCESS 0
#define PMM_STATUS_CANNOT_ALLOC_NODE 1
#define PMM_STATUS_PAGE_NOT_FOUND 2
#define PMM_STATUS_INVALID_ARGUMENTS 3
#define PMM_STATUS_INIT_UNALIGNED 4
#define PMM_STATUS_NOT_ENOUGH_PAGE 5

//#define PMM_PAGE_ATTR_FREE_BIT 0
//#define PMM_PAGE_ATTR_PAGED_BIT 1
//
//typedef struct
//{
//    uint32_t attr;
//} k_physical_page_attr_t;

typedef struct
{
    avl_tree_t active_tree;
    linked_list_t free_list;
    k_spin_lock_t lock;
    _Bool initialized;
} k_pmm_descriptor_t;

int32_t KAPI k_pmm_init(k_pmm_info_t *info, k_pmm_descriptor_t *desc);

int32_t KAPI k_alloc_page(k_pmm_descriptor_t *desc, k_physical_addr_t *out);

int32_t KAPI k_free_page(k_pmm_descriptor_t *desc, k_physical_addr_t base);

// TODO: implement these somehow, i might just reserve the first 16MB for these
int32_t KAPI k_alloc_contiguous_pages(k_pmm_descriptor_t *desc,
                                      uint64_t num_of_page,
                                      k_physical_addr_t highest_p_addr,
                                      k_physical_addr_t *out);

int32_t KAPI k_free_contiguous_pages(k_pmm_descriptor_t *desc,
                                     k_physical_addr_t base);

#endif