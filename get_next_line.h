#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE
#endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	 	*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
char	    *ft_strdup(const char *s);
char        *ft_strjoin(char const *s1, char const *s2);
size_t      ft_strlen(const char *s);
char    	*ft_substr(char const *s, size_t start, size_t len);

#endif