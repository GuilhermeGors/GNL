/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:10:56 by gugomes-          #+#    #+#             */
/*   Updated: 2024/11/12 18:09:27 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	ft_free(char **to_free)
{
	if (to_free && *to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

static char *fill_line(int fd, char *rest)
{
    char buffer[BUFFER_SIZE + 1];
    ssize_t b_read;
    char *temp;

    b_read = read(fd, buffer, BUFFER_SIZE);
    while (b_read > 0)
    {
        buffer[b_read] = '\0';
        if (!rest)
            rest = ft_strdup("");
        temp = rest;
        rest = ft_strjoin(rest, buffer);
        ft_free(&temp);
        if (ft_strchr(buffer, '\n'))
            break;
        b_read = read(fd, buffer, BUFFER_SIZE);
    }
    return (rest);
}

static char *append_line(char *line_buffer)
{
    ssize_t i = 0;

    if (!line_buffer)
        return (ft_free(&line_buffer), NULL);
    while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
        i++;
    if (line_buffer[i] == '\n' && line_buffer[i + 1] == '\0')
        return (NULL);
    return (ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i - 1));
}

char *get_next_line(int fd)
{
    static char *rest;
    char *line;
    char *new_rest;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (ft_free(&rest), NULL);
    rest = fill_line(fd, rest);
    if (!rest)
        return (NULL);
    if (rest[0] == '\n')
    {
        line = ft_strdup("\n");
        new_rest = append_line(rest);
        ft_free(&rest);
        rest = new_rest;
        return (line);
    }
    if (!ft_strchr(rest, '\n'))
    {
        line = ft_strdup(rest);
        ft_free(&rest);
        return (line);
    }
    line = ft_substr(rest, 0, ft_strchr(rest, '\n') - rest + 1);
    new_rest = append_line(rest);
    ft_free(&rest);
    rest = new_rest;
    return (line);
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
