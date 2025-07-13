

#include "libft.h"


void ft_putendl_fd(char *s , int fd){
    if(!s) return ;
    char new_line = '\n';
    ft_putstr_fd(s , fd);
    write(fd , &new_line , sizeof(char));
}
