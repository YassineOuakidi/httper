
#include "libft.h"


void ft_bzero(void *ptr , size_t n){

    size_t i = 0;
    while(i<n){
        *(unsigned char *)(ptr+i) = 0;
        i++;
    }
}
