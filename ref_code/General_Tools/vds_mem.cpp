#include "vds_mem.h"


void *vmalloc(int size){
    return calloc( 1, size ) ;
}
void vfree(void *p){ 
    free (p) ;
}
