

#include "libft.h"


size_t ft_strlcpy(char* dst , char* src , size_t len){
    size_t i = 0;
    if(!src || !dst)
        return 0;
    while(i+1<len && src[i]){
        *(unsigned char*)(dst + i ) = *(unsigned char*)(src+i);
        i++;
    }
    if(len>0)
        *(unsigned char*)(dst + i ) = '\0';
    return ft_strlen(src);
}
