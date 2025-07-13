

#include "libft.h"


void ft_putstr_fd(char *s , int fd){
    if(!s) return ;
    size_t i = 0;
    while(s[i]){

        write(fd , (s+i) , sizeof(char));
        i++;
    }

}
