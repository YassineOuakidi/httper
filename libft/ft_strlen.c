

#include "libft.h"


size_t ft_strlen(char* s){
    
    size_t tmp = 0;
    while(*s){
        tmp++;
        s++;
    }
    return tmp;

}
