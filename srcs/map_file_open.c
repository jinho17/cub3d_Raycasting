/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 17:43:18 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 12:56:05 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		get_next_line(int fd, int *rd_size)
{
	char	line[1024];
	char	buf;
	int		i;

	i = 0;
	while (1)
	{
		*rd_size = read(fd, &buf, 1);
		if (buf == '\n')
			break ;
		line[i++] = buf;
	}
	if (i > 0)
	{
		line[i] = '\0';
		if (0 > get_map_info(line))
			return (-1);
	}
	return (fd);
}

int		file_open(int fd)
{
	int	rd_size;

	rd_size = 1;
	while (rd_size != 0)
	{
		fd = get_next_line(fd, &rd_size);
		if (fd == -1)
		{
			ft_putstr_fd("Error\nInvalid map format.\n", 1);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int		argc_error_check(int argc)
{
	if (argc > 4)
	{
		ft_putstr_fd("Error\nInvalid options!\n", 1);
		return (-1);
	}
	else if (argc == 1)
	{
		ft_putstr_fd("Error\nInput map filename!\n", 1);
		return (-1);
	}
	return (0);
}

int		map_file_open(int argc, char *argv[])
{
	int		fd;

	if (argc_error_check(argc) < 0)
		return (-1);
	if (0 < (fd = open(argv[1], O_RDONLY)))
	{
		if (0 > file_open(fd))
			return (-1);
	}
	else
	{
		ft_putstr_fd("Error\nCannot open map file.\n", 1);
		return (-1);
	}
	return (0);
}
