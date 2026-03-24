#ifndef _VDS_MEM_H_
#define _VDS_MEM_H_

#include <stdlib.h>

void *vmalloc(int size);
void vfree(void *p);

#endif