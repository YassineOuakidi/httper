

#include "libft.h"



void *ft_calloc(size_t nmemb , size_t size){
    if(nmemb==0 || size==0) return malloc(0);
    void *arr = malloc(nmemb * size);
    if(!arr)
        return NULL;
    ft_memset(arr , 0 , size * nmemb);
    return arr;

}
