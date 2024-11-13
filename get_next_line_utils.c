/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugomes- <gugomes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:04:35 by gugomes-          #+#    #+#             */
/*   Updated: 2024/11/13 17:35:46 by gugomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len])
        len++;
    return len;
}

char *ft_strdup(const char *src)
{
    size_t len = ft_strlen(src);
    char *dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;

    size_t i = 0;
    while (i < len)
    {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

char *ft_strchr(const char *s, int c)
{
    while (s && *s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return (c == '\0') ? (char *)s : NULL;
}

char *ft_substr(const char *s, size_t start, size_t len)
{
    if (!s || start >= ft_strlen(s))
        return NULL;
    size_t max_len = ft_strlen(s) - start;
    if (len > max_len)
        len = max_len;

    char *sub = (char *)malloc((len + 1) * sizeof(char));
    if (!sub)
        return NULL;
    size_t i = 0;
    while (i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return sub;
}

char *ft_strjoin(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return NULL;

    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!str)
        return NULL;
    size_t i = 0;
    while (i < len1)
    {
        str[i] = s1[i];
        i++;
    }
    size_t j = 0;
    while (j < len2)
    {
        str[i] = s2[j];
        i++;
        j++;
    }
    str[i] = '\0';
    return str;
}

