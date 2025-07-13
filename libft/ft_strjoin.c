#include "libft.h"


char *ft_strjoin(char *s1 , char *s2){
    if(!s2 && !s1) return ft_strdup("");
    if(!s1) return ft_strdup(s2);
    if(!s2) return ft_strdup(s1);
    size_t tmp = ft_strlen(s1) , tmp2 = ft_strlen(s2);
    char *ans =malloc(tmp + tmp2 +1);
    if(!ans) return NULL;
    size_t i =0;
    while(i<tmp ){
        ans[i] = s1[i];i++;
    }
    while(i-tmp<tmp2){
        ans[i] = s2[i - tmp];i++;
    }
    ans[i] = '\0';
    return ans;
}
