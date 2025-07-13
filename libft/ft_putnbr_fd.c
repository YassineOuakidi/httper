

#include "libft.h"



void ft_putnbr_fd(int n , int fd){

    char *num = ft_itoa(n);
    if(!num) return ;
    ft_putstr_fd(num , fd);
    free(num);
}
