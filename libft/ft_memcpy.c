

#include "libft.h"


void *ft_memcpy(void *dst , const void *source , size_t size){

    size_t i = 0;
    while(i<size){
        *(unsigned char*)(dst + i) = *(unsigned char *)(source + i);
        i++;
    }
    return dst;
}
