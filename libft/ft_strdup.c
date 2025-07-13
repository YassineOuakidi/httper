


#include "libft.h"


char *ft_strdup(char * s){
    size_t  len = ft_strlen(s);
    char *ans = malloc(len+1);
    if(!ans)
        return NULL;
    ft_strlcpy(ans , s , len+1);
    return ans;
}
