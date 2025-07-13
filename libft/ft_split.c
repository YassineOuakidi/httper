#include "libft.h"

static size_t count_words(const char *s1, int c) {
    size_t count = 0, i = 0;
    int in_word = 0;

    while (s1[i]) {
        if (s1[i] != c) { 
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
        i++;
    }
    return count;
}

char **ft_split(const char *s1, int c) {
    if (!s1) return NULL;

    size_t word_count = count_words(s1, c);
    char **split = (char **)malloc((word_count + 1) * sizeof(char *));
    if (!split) return NULL;

    size_t i = 0, j = 0, word_index = 0;

    while (word_index < word_count) {
        while (s1[i] == c) i++; 

        j = 0;
        while (s1[i + j] && s1[i + j] != c) j++; 

        split[word_index] = (char *)malloc((j + 1) * sizeof(char));
        if (!split[word_index]) {
            for (size_t k = 0; k < word_index; k++) {
                free(split[k]);
            }
            free(split);
            return NULL;
        }

        ft_memcpy(split[word_index], s1 + i, j);
        split[word_index][j] = '\0';

        i += j;
        word_index++;
    }

    split[word_count] = NULL;
    return split;
}
