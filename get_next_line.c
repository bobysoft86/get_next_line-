/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:06:42 by roberodr          #+#    #+#             */
/*   Updated: 2023/03/08 12:50:22 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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

char	*get_next_line( int fd)
{	
	static char	*buffer = NULL;
	char		*line;
	int			byte_read;

	byte_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (gnl_free (&buffer));
	if (!buffer || (buffer && !gnl_strchr(buffer, '\n')))
		buffer = gnl_chek_file (fd, buffer, byte_read);
	if (!buffer)
		return (NULL);
	line = gnl_getline (buffer);
	if (!line)
	{
		gnl_free (&buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = gnl_next (buffer);
	return (line);
}

//   int	main(void)
// {
//  	char	*line;
//  	int		fd_1;
//  	int		i;
//   	fd_1 = open("test/test1.txt", O_RDONLY);
//  	i = 1;
//  	while (i)
// 	{
//  		line = get_next_line(fd_1);
//  		if (!line)
//  			return (0);
//  		printf("Line %d for fd %d: %s <%zu>\n", i, fd_1, line, strlen(line));
//  		free(line);
//  		i++;
//  	}
// }