

#include "libft.h"



void *ft_memset(void *ptr , int value , size_t size){
    if(!ptr)
        return NULL;
    size_t i=0;
    while(i<size){
        *(unsigned char *)(ptr+i) = value;
        i++;
    }
    return ptr;
}
