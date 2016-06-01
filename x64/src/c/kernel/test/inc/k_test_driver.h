#ifndef _K_TEST_DRIVER_H_
#define _K_TEST_DRIVER_H_

#include "k_type.h"
#include "k_def.h"

void KAPI test_begin(char *name);

void KAPI test_end();

void *KAPI talloc(uint32_t size);

void KAPI run_case(char *name, bool result);

#endif