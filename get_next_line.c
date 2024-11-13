/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:10:56 by gugomes-          #+#    #+#             */
/*   Updated: 2024/11/13 18:24:44 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

char *ft_realloc(char *ptr, size_t old_size, size_t new_size)
{
    char *new_ptr;

    if (new_size <= old_size)
        return ptr;
    new_ptr = (char *)malloc(new_size);
    if (!new_ptr)
    {
        free(ptr);
        return NULL;
    }
    ft_memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}

static char *read_and_fill(int fd, char *rest)
{
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    size_t rest_len = rest ? ft_strlen(rest) : 0;

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        char *temp = ft_realloc(rest, rest_len, rest_len + bytes_read + 1);
        if (!temp)
            return NULL;
        rest = temp;
        ft_memcpy(rest + rest_len, buffer, bytes_read + 1);
        rest_len += bytes_read;
        if (ft_strchr(buffer, '\n'))
            break;
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    if (bytes_read == 0 && (!rest || rest[0] == '\0'))
    {
        free(rest);
        return NULL;
    }
    return rest;
}

static char *extract_line_and_update_rest(char **rest)
{
    size_t len = 0;
    char *line;
    char *new_rest;

    if (!*rest)
        return NULL;
    while ((*rest)[len] && (*rest)[len] != '\n')
        len++;
    
    if ((*rest)[len] == '\n')
        line = ft_substr(*rest, 0, len + 1);
    else
        line = ft_substr(*rest, 0, len);
    
    if (!line)
        return NULL;
    
    if ((*rest)[len] == '\n')
        new_rest = ft_substr(*rest, len + 1, ft_strlen(*rest) - len);
    else
        new_rest = ft_substr(*rest, len, ft_strlen(*rest) - len);
    
    free(*rest);
    *rest = new_rest;
    return line;
}

char *get_next_line(int fd)
{
    static char *rest;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        free(rest);
        rest = NULL;
        return NULL;
    }
    rest = read_and_fill(fd, rest);
    if (!rest)
        return NULL;
    
    line = extract_line_and_update_rest(&rest);
    if (!line)
    {
        free(rest);
        rest = NULL;
    }
    return line;
}


// int main(void)
// {
//     int fd;
//     char *line;
    
//     fd = open("read_error.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("Erro ao abrir o arquivo");
//         return 1;
//     }
//     while ((line = get_next_line(fd)) != NULL)
// 	{
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
//     return 0;
// }