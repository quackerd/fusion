/* Copyright 2016 secXsQuared
 * Distributed under GPL license
 * See COPYING under root for details
 */

#include "std_lib.h"

static uint32_t seed = 1;
static uint32_t max = 16777215;

uint32_t KAPI rand( void )
{
    seed = seed * 1103512986 + 29865;
    return (unsigned int)(seed / 65536) % (max+1);
}

void KAPI srand( uint32_t _seed )
{
    seed = _seed;
}

void KAPI mrand(uint32_t _max)
{
    max = _max;
}