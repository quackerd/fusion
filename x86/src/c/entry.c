#include "type32.h"
#include "kdef32.h"
#include "grub.h"
#include "mem32.h"
uint8 g_gdt[8*8];
gdt_ptr g_gdt_ptr;
uint8 g_idt[8*256];
idt_ptr g_idt_ptr;

extern word* kernel_stack;

void HYPKERNEL32 print_str(char* str)
{
    uint8* gram = (uint8*)0x0b8000;
    while(*str != 0)
    {
        *gram = (uint8)*str;
        gram++;
	    *gram = 7;
	    gram++;
	    str++;
    }
    return;
}

int32 HYPKERNEL32 hk_main(multiboot_info_t* multiboot_info)
{
    segment_descriptor desc_dummy = {.DPL = 0, .Pr = 0, .x64 = 0, .Sys = 0, .type = 0, .Sz = 0, .limit = 0,.Gr = 0,.base = 0, .Avl = 0};
    segment_descriptor desc = {.Gr = 1,.Pr = 1 ,.Sz = 1, .Avl = 0,.Sys = 1, .x64 = 0 ,.base = 0,.limit = 0xFFFFF};

    //dummy descriptor
    hk_set_segment_descriptor(&g_gdt[0], &desc_dummy);
    //ring 0 code seg, non-conforming
    desc.type = 10;
    desc.DPL = 0;
    hk_set_segment_descriptor(&g_gdt[8], &desc);
    //ring 3 code seg
    desc.DPL = 3;
    hk_set_segment_descriptor(&g_gdt[16], &desc);
    //ring 0 data RW
    desc.DPL = 0;
    desc.type = 2;
    hk_set_segment_descriptor(&g_gdt[24], &desc);
    //ring 3 data
    desc.DPL = 3;
    hk_set_segment_descriptor(&g_gdt[32], &desc);
    g_gdt_ptr.limit = 8*8-1;
    g_gdt_ptr.base = (uint32)g_gdt;
    hk_load_gdt(&g_gdt_ptr);

    char* msg = "Welcome to HYP OS 1.0";
    print_str(msg);

    loop:
        goto loop;
}