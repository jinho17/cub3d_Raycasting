/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 11:55:39 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 13:33:44 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_bmp(int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = g_screen.height;
	pad = (4 - (g_screen.width * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < g_screen.width)
		{
			write(fd, &(g_buf[i][j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

void	bmp_header(int fd, int size)
{
	unsigned char	header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	header[18] = (unsigned char)(g_screen.width);
	header[19] = (unsigned char)(g_screen.width >> 8);
	header[20] = (unsigned char)(g_screen.width >> 16);
	header[21] = (unsigned char)(g_screen.width >> 24);
	header[22] = (unsigned char)(g_screen.height);
	header[23] = (unsigned char)(g_screen.height >> 8);
	header[24] = (unsigned char)(g_screen.height >> 16);
	header[25] = (unsigned char)(g_screen.height >> 24);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

int		save_bmp(void)
{
	int fd;
	int size;

	size = 54 + 3 * g_screen.width * g_screen.height;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT
					| O_TRUNC | O_APPEND, 00755)) < 0)
		return (-1);
	bmp_header(fd, size);
	write_bmp(fd);
	exit(0);
	return (0);
}
