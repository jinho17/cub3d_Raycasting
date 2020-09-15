/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dir_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 11:54:10 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 11:55:21 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	east_west(int x, int y)
{
	if (g_map[x][y] == 'E')
	{
		g_info.plane.x = 0.66;
		g_info.plane.y = 0;
		g_info.dir.x = 0;
		g_info.dir.y = 1;
	}
	else if (g_map[x][y] == 'W')
	{
		g_info.plane.x = -0.66;
		g_info.plane.y = 0;
		g_info.dir.x = 0;
		g_info.dir.y = -1;
	}
}

void	north_south(int x, int y)
{
	if (g_map[x][y] == 'N')
	{
		g_info.plane.x = 0;
		g_info.plane.y = 0.66;
		g_info.dir.x = -1;
		g_info.dir.y = 0;
	}
	else if (g_map[x][y] == 'S')
	{
		g_info.plane.x = 0;
		g_info.plane.y = -0.66;
		g_info.dir.x = 1;
		g_info.dir.y = 0;
	}
}

void	init_pos_dir(void)
{
	int x;
	int y;

	y = 0;
	while (y < g_m.height)
	{
		x = 0;
		while (x < g_m.width)
		{
			if (g_map[x][y] == 'N' || g_map[x][y] == 'S'
				|| g_map[x][y] == 'E' || g_map[x][y] == 'W')
			{
				g_info.pos.x = x;
				g_info.pos.y = y;
				north_south(x, y);
				east_west(x, y);
				break ;
			}
			x++;
		}
		y++;
	}
}
