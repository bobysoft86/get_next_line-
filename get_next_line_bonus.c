/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:06:42 by roberodr          #+#    #+#             */
/*   Updated: 2023/03/08 13:00:25 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

char	*create(char *s1)
{
	s1 = malloc (sizeof(char) * 1);
	if (!s1)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*gnl_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*refree(char	*buffer, char	*res )
{
	gnl_free (&buffer);
	free (res);
	return (NULL);
}

char	*gnl_chek_file(int fd, char *res, int byte_read)
{
	char	*buffer;

	buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		gnl_free(&res);
		return (NULL);
	}
	buffer[0] = '\0';
	while (byte_read > 0 && !gnl_strchr(buffer, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			refree(buffer, res);
		buffer[byte_read] = 0;
		if (byte_read > 0)
		{
			res = gnl_strjoin(res, buffer);
			if (!res)
				return (refree(buffer, res));
		}
	}
	gnl_free (&buffer);
	return (res);
}

char	*get_next_line(int fd)
{	
	static char	*buffer[OPEN_MAX];
	char		*line;
	int			byte_read;

	byte_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (gnl_free (&buffer[fd]));
	if (!buffer[fd] || (buffer[fd] && !gnl_strchr(buffer[fd], '\n')))
		buffer[fd] = gnl_chek_file (fd, buffer[fd], byte_read);
	if (!buffer[fd])
		return (NULL);
	line = gnl_getline (buffer[fd]);
	if (!line)
	{
		gnl_free (&buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = gnl_next (buffer[fd]);
	return (line);
}
