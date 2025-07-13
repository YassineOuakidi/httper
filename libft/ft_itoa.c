#include "libft.h"


static int get_number_len(int n) {
    int len = (n <= 0) ? 1 : 0;
    while (n) {
        len++;
        n /= 10;
    }
    return len;
}

char *ft_itoa(int n) {
    int len = get_number_len(n);
    char *answer = malloc((len + 1) * sizeof(char));
    if (!answer) return NULL;

    answer[len] = '\0';  
    long num = n;   

    if (num < 0) {
        answer[0] = '-';
        num = -num;
    }

    while (len-- > (n < 0)) {  
        answer[len] = (num % 10) + '0';
        num /= 10;
    }

    return answer;
}
