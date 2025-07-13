

#include "libft.h"


char *ft_strtrim(char *s1 , char *set){
    if(!s1 || !set) return NULL;
    size_t i =0 ;
    size_t j =ft_strlen(s1);
    while(s1[i] && ft_strchr(set , s1[i])) i++;
    while(j>i && ft_strchr(set , s1[j-1])) j--;
    return ft_substr(s1 , i , j-i);
}
