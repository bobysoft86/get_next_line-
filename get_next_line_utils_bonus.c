/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:09:13 by roberodr          #+#    #+#             */
/*   Updated: 2023/03/08 11:20:22 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int	gnl_strlen(const char *c)
{
	int	count;	

	count = 0;
	while (c[count])
		count++;
	return (count);
}

char	*gnl_getline(char *buffer)
{
	char	*line ;
	int		cont;

	cont = 0;
	if (!buffer[cont])
		return (NULL);
	while (buffer[cont] && buffer[cont] != '\n')
		cont++;
	if (buffer[cont] == '\n')
		line = malloc((cont + 2) * sizeof(char));
	else
		line = malloc((cont + 1) * sizeof(char));
	if (!line)
		return (NULL);
	cont = 0;
	while (buffer[cont] && buffer[cont] != '\n')
	{
		line[cont] = buffer[cont];
		cont++;
	}
	if (buffer[cont] && buffer[cont] == '\n')
		line[cont++] = '\n';
	line[cont] = '\0';
	return (line);
}

char	*gnl_next(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	line = malloc((gnl_strlen (buffer) - i + 1) * sizeof (char));
	if (!line)
		return (gnl_free(&buffer));
	i++;
	j = 0;
	while (buffer[i])
	{
		line[j++] = buffer[i++];
	}
	line[j] = '\0';
	gnl_free(&buffer);
	return (line);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*total;

	if (!s1)
	{
		s1 = create(s1);
		if (!s1)
			return (NULL);
	}
	total = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!total)
		return (gnl_free(&s1));
	i = -1;
	while (s1[++i] != '\0')
		total[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		total[i + j] = s2[j];
	total[i + j] = '\0';
	gnl_free (&s1);
	return (total);
}
