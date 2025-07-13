#include "libft.h"

const char* ft_strchr(const char* s, int c) {
    size_t i = 0;
    if (!s) return NULL;
    while (s[i]) {
        if (*(unsigned char*)(s + i) == (unsigned char)c) {
            return (s + i);
        }
        i++;
    }
    if ((unsigned char)c == '\0') {
        const char *ans = (s + i);
        return ans;
    }
    return NULL;
}
