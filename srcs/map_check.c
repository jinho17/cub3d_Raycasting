/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:59:13 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/10 16:00:47 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		zero_check_y(int x, int y)
{
	int	i;

	i = 1;
	while (y + i < g_m.height)
	{
		if (g_map[x][y + i] == '1')
			break ;
		else if (g_map[x][y + i] == ' ')
			return (-1);
		i++;
	}
	if (y + i == g_m.height)
		return (-1);
	i = 1;
	while (y - i >= 0)
	{
		if (g_map[x][y - i] == '1')
			break ;
		else if (g_map[x][y - i] == ' ')
			return (-1);
		i++;
	}
	if (y - i == -1)
		return (-1);
	return (0);
}

int		zero_check(int x, int y)
{
	int i;

	i = 1;
	while (x + i < g_m.width)
	{
		if (g_map[x + i][y] == '1')
			break ;
		else if (g_map[x + i][y] == ' ')
			return (-1);
		i++;
	}
	if (x + i == g_m.width)
		return (-1);
	i = 1;
	while (x - i >= 0)
	{
		if (g_map[x - i][y] == '1')
			break ;
		else if (g_map[x - i][y] == ' ')
			return (-1);
		i++;
	}
	if (x - i == -1)
		return (-1);
	return (0);
}

int		map_zero_check(int x, int y)
{
	while (y < g_m.height)
	{
		x = 0;
		while (x < g_m.width)
		{
			if (g_map[x][y] == '0' || g_map[x][y] == '2' || g_map[x][y] == 'S'
			|| g_map[x][y] == 'W' || g_map[x][y] == 'E' || g_map[x][y] == 'N')
			{
				if (0 > zero_check(x, y))
					return (-1);
				if (0 > zero_check_y(x, y))
					return (-1);
				if (g_map[x][y] != '0' && g_map[x][y] != '2')
				{
					if (g_m.check_pos == 1)
						return (-1);
					else if (g_m.check_pos == 0)
						g_m.check_pos = 1;
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}

int		map_edge_check(void)
{
	int x;
	int y;

	y = 0;
	while (y < g_m.height)
	{
		x = 0;
		while (x < g_m.width)
		{
			if (x == 0 || x == g_m.width - 1 || y == 0 || y == g_m.height - 1)
			{
				if (g_map[x][y] != '1' &&
					g_map[x][y] != ' ' && g_map[x][y] != 0)
					return (-1);
			}
			if (g_map[x][y] == '2')
				g_sp.num += 1;
			x++;
		}
		y++;
	}
	return (0);
}

int		map_check(int x, int y)
{
	if (0 > map_edge_check())
		return (-1);
	g_m.check_pos = 0;
	if (0 > map_zero_check(0, 0))
		return (-1);
	if (g_m.check_pos == 0)
		return (-1);
	while (y < g_m.height && g_map[x][y] != '1')
		y++;
	while (x < g_m.width)
	{
		if (g_map[x][y + 1] == '1')
			break ;
		x++;
	}
	g_dfs.x = x;
	g_dfs.y = y + 1;
	g_dfs.width = 0;
	g_dfs.height = 0;
	dfs(x, y);
	if (g_dfs.width != g_m.width - 1 || g_dfs.height != g_m.height - 1)
		return (-1);
	return (0);
}
