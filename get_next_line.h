#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE
#endif

typedef struct s_list {
    char            *content;
    struct s_list   *next;
} t_list;

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	 	*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(char *src);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, char *src, unsigned int  size);
void		*ft_calloc(size_t num, size_t nsize);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
t_list		*ft_lstnew(void *content);
void		*ft_memset(void *s, int c, size_t n);
char	    *ft_substr(char const *s, unsigned int start, size_t len);

#endif