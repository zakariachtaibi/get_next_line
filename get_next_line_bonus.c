/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchtaibi <zchtaibi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:00:27 by zchtaibi          #+#    #+#             */
/*   Updated: 2023/12/11 15:18:17 by zchtaibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_find(char c, char *str)
{
	int	index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	if (!c && !str[index])
		return (index);
	return (-1);
}

char	*ft_fill_stash(int fd, char *stash, int *new_line)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		*new_line = ft_find('\n', stash);
		if (*new_line >= 0)
			break ;
	}
	free(buffer);
	return (stash);
}

char	*ft_extract_line(char *stash, int new_line)
{
	char	*line;
	char	*temp;

	if (!stash)
		return (NULL);
	if (new_line >= 0)
	{
		temp = ft_substr(stash, 0, new_line + 1);
		line = ft_strjoin(NULL, temp);
		free(temp);
	}
	else
		line = ft_strjoin(NULL, stash);
	return (line);
}

char	*ft_process_stash(char *stash, int new_line)
{
	char	*temp;

	if (!stash)
		return (NULL);
	if (new_line < 0)
	{
		free(stash);
		return (NULL);
	}
	temp = ft_substr(stash, new_line + 1, ft_strlen(stash));
	free(stash);
	stash = temp;
	return (stash);
}	

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD + 1];
	char		*line;
	int			new_line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_fill_stash(fd, stash[fd], &new_line);
	if (!stash[fd])
		return (NULL);
	if (!*stash[fd])
	{
		free(stash[fd]);
		return (NULL);
	}
	line = ft_extract_line(stash[fd], new_line);
	stash[fd] = ft_process_stash(stash[fd], new_line);
	return (line);
}
// #include <stdio.h>
// int main()
// {
//     int fd1 = open("get_next_line.c", O_RDONLY);
//     int fd2 = open("get_next_line.h", O_RDONLY);
//     char *line1;
//     char *line2;
//     while((line1 = get_next_line(fd1)))
// 	{
// 		printf("line1: %s", line1);
// 		free(line1);
// 	}
// 	printf("\n");
// 	while ((line2 = get_next_line(fd2)))
// 	{
// 		printf("line2: %s", line2);
// 		free(line2);
// 	}
// 	return (0);
// }