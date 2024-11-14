/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:10:56 by gugomes-          #+#    #+#             */
/*   Updated: 2024/11/14 16:33:26 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_realloc(char *ptr, size_t old_size, size_t new_size)
{
	char	*new_ptr;

	if (new_size <= old_size)
		return (ptr);
	new_ptr = (char *)malloc(new_size);
	if (!new_ptr)
		return (free(ptr), NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

static char	*read_and_fill(int fd, char *rest, size_t rest_len, ssize_t b_read)
{
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(buffer), free(rest), NULL);
	b_read = read(fd, buffer, BUFFER_SIZE);
	if (b_read < 0)
		return (free(rest), free(buffer), NULL);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		rest = ft_realloc(rest, rest_len, rest_len + b_read + 1);
		if (!rest)
			return (free(buffer), NULL);
		ft_memcpy(rest + rest_len, buffer, b_read + 1);
		rest_len += b_read;
		if (ft_strchr(buffer, '\n'))
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
			return (free(rest), NULL);
	}
	if (b_read < 0 || (b_read == 0 && (rest == NULL || rest[0] == '\0')))
		return (free(rest), free(buffer), NULL);
	return (free(buffer), rest);
}

static char	*extract_line_and_update_rest(char **rest)
{
	size_t	len;
	char	*line;
	char	*new_rest;

	len = 0;
	if (!*rest)
		return (NULL);
	while ((*rest)[len] && (*rest)[len] != '\n')
		len++;
	if ((*rest)[len] == '\n')
		line = ft_substr(*rest, 0, len + 1);
	else
		line = ft_substr(*rest, 0, len);
	if (!line)
		return (NULL);
	if ((*rest)[len] == '\n')
		new_rest = ft_substr(*rest, len + 1, ft_strlen(*rest) - len);
	else
		new_rest = ft_substr(*rest, len, ft_strlen(*rest) - len);
	free(*rest);
	*rest = new_rest;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	size_t		rest_len;
	ssize_t		b_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	rest_len = 0;
	if (rest != NULL)
		rest_len = ft_strlen(rest);
	b_read = 1;
	rest = read_and_fill(fd, rest, rest_len, b_read);
	if (!rest)
		return (NULL);
	line = extract_line_and_update_rest(&rest);
	if (!line)
	{
		free(rest);
		rest = NULL;
	}
	return (line);
}
