#ifndef LIBFT_H
#define LIBFT_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>



int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);
size_t ft_strlen(char* s);
void *ft_memset(void *ptr , int value , size_t size);
void ft_bzero(void *ptr , size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);
void * ft_memcpy(void *dst , const void *source , size_t size);
void * ft_memmove ( void * destination, const void * source, size_t num );
size_t ft_strlcpy (char* dst , char* src , size_t len);
size_t ft_strlcat (char* dst , char* src , size_t len);
int ft_toupper(int c);
int ft_tolower(int c);
const char* ft_strchr(const char* s , int c);
char* ft_strrchr(const char* s , int c);
int ft_strncmp(const char *s1 , const char *s2 , size_t n);
void *ft_memchr(const void *s , int c , size_t n);
char *ft_strnstr(const char *big , const char *little , size_t len);
int ft_atoi(const char *nptr);
void *ft_calloc(size_t nmemb , size_t size);
char *ft_strdup(char *s);
char *ft_substr(char *s , unsigned int start , size_t len);
char *ft_strjoin(char *s1 ,char *s2);
char *ft_strtrim(char *s1 , char *set);
char **ft_split(const char *s1 , int c);
char *ft_itoa(int n);
char *ft_strmapi(char *s , char (*f)(unsigned int , char ));
void ft_striteri(char *s , void (*f)(unsigned int , char*));
void ft_putchar_fd(char c , int fd);
void ft_putnbr_fd(int n , int fd);
void ft_putstr_fd(char *s , int fd);
void ft_putendl_fd(char *s , int fd);
#endif
