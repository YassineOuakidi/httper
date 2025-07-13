#include "libft.h"

char *ft_substr(char *s , unsigned int start , size_t len){
    if(!s)
        return NULL;
    size_t str_len = ft_strlen(s);
    if(start>=str_len){
        return ft_strdup("");
    }
    if(len> str_len - start){
        len = str_len - start;
    }
    char *ans = malloc(len+1);
    if(!ans) return NULL;
    ft_strlcpy(ans , s+start , len+1);
    return ans;
}
