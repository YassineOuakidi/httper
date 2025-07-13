

#include "libft.h"


void ft_striteri(char *s , void (*f)(unsigned int , char*)){
    if(!s || !f) return ;
    size_t i = 0 ;
    while(s[i]){
        f(i , s+i);
        i++;
    }
}
