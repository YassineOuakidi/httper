

#include "libft.h"

void *ft_memmove(void *destination , const void *source , size_t num){
    int i=0 ;
    if(destination < source){
        while(i<(int)num){
            *(unsigned char*)(destination + i) = *(unsigned char*)(source + i);
            i++;
        }
        return destination;
    } else {
        i = num-1;
        while(i>=0){
            *(unsigned char *)(destination + i) = *(unsigned char *)(source + i);
            i--;
        }
        return destination;
    }
}
