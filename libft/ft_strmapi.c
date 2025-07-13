

#include "libft.h"


char *ft_strmapi(char *s , char (*f)(unsigned int , char)){
    if(!s || !f) return NULL;
    size_t strlen = ft_strlen(s);
    char *ans = (char *)malloc(strlen + 1);
    if(!ans) return NULL;
    size_t i = 0;
    while(s[i]){
        ans[i] = f(i , s[i]);
        i++;
    }
    ans[i] = '\0';
    return ans;

}
