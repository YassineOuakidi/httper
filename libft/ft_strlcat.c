

#include "libft.h"


size_t ft_strlcat(char *dst , char* src , size_t len){
    size_t dst_len = ft_strlen(dst) , i=0 , index = 0;
    while(*(unsigned char*)(dst + index))
        index++;
    while((i + index + 1 < len) && src[i]){
        *(unsigned char*)(dst + index + i) = *(unsigned char*)(src+i);
        i++ ;
    }
    if(index + i + 1<len){
        *(unsigned char*)(dst + i) = '\0';
    }
    if(len<dst_len){
        return len + ft_strlen(src);
    } else {
        return dst_len + ft_strlen(src);
    }
}
