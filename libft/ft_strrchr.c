

#include "libft.h"

char* ft_strrchr(const char* s , int c){
    
    char* tmp = NULL;
    size_t i =0;
    while(s[i]){
        if((unsigned char)s[i]==(unsigned char)c)
            tmp = (char *)(s+i);
        i++;
    }
    if((unsigned char)c=='\0')
        return (char *)(s+i);
    return tmp;
}
