/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:10:56 by gugomes-          #+#    #+#             */
/*   Updated: 2024/11/06 15:40:29 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	add_to_list(t_list **head, char *buffer, int len)
{
	t_list	*new_node;
	int		i;

	new_node = ft_lstnew(ft_calloc(len + 1, sizeof(char)));
	if (!new_node || !new_node->content)
	{
		free(new_node);
		return;
	}
	i = 0;
	while (i < len && buffer[i])
	{
		((char *)new_node->content)[i] = buffer[i];
		i++;
	}
	((char *)new_node->content)[i] = '\0';
	ft_lstadd_back(head, new_node);
}

static char	*get_line_from_list(t_list *head)
{
	int		total_len;
	char	*line;
	int		i;
	t_list	*node;

	total_len = 0;
	node = head;
	while (node)
	{
		total_len += ft_strlen((char *)node->content);
		node = node->next;
	}
	line = ft_calloc(total_len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	node = head;
	while (node)
	{
		ft_strlcpy(&line[i], (char *)node->content, ft_strlen((char *)node->content) + 1);
		i += ft_strlen((char *)node->content);
		node = node->next;
	}
	return (line);
}

static void	free_list(t_list **head)
{
	ft_lstclear(head, free);
	*head = NULL;
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	int				bytes_read;
	static t_list	*head = NULL;
	char			*line;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		add_to_list(&head, buffer, bytes_read);
		if (ft_strchr(buffer, '\n'))
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0 || (bytes_read == 0 && !head))
	{
		free_list(&head);
		return (NULL);
	}
	line = get_line_from_list(head);
	free_list(&head);
	return (line);
}



#include <stdio.h>

int main(void)
{
    int fd = open("teste", O_RDONLY);
    //char *line;

    // while ((line = get_next_line(fd)) != NULL)
    // {
    //     printf("%s", line);
    //     free(line);
    // }

	printf("%s", get_next_line(fd));
    close(fd);
    return (0);
}