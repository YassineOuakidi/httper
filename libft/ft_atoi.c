



#include "libft.h"
#include <limits.h>
static int ft_isspace(int c)
{
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int ft_atoi(const char *nptr)
{
    int sign = 1;
    long result = 0;
    size_t i = 0;

    while (ft_isspace(nptr[i]))
        i++;

    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            sign = -1;
        i++;
    }

    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        result = result * 10 + (nptr[i] - '0');
        i++;

        if (result > INT_MAX)
        {
            if (sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
    }

    return (int)(result * sign);
}
