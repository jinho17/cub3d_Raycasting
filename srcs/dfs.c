/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:08:20 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/10 16:09:10 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	back(int x, int y)
{
	g_map_c[x][y] = 2;
	if (g_map[x + 1][y] == '1' && g_map_c[x + 1][y] == 1)
		dfs(x + 1, y);
	else if (g_map[x - 1][y] == '1' && g_map_c[x - 1][y] == 1)
		dfs(x - 1, y);
	else if (g_map[x][y + 1] == '1' && g_map_c[x][y + 1] == 1)
		dfs(x, y + 1);
	else if (g_map[x][y - 1] == '1' && g_map_c[x][y - 1] == 1)
		dfs(x, y - 1);
}

void	dfs(int x, int y)
{
	if (x == g_dfs.x && y == g_dfs.y && g_map_c[x][y] == 0)
		return ;
	g_map_c[x][y] = 1;
	if (g_dfs.width < x)
		g_dfs.width = x;
	if (g_dfs.height < y)
		g_dfs.height = y;
	while (1)
	{
		if (g_map[x + 1][y] == '1' && g_map_c[x + 1][y] == 0)
			dfs(x + 1, y);
		else if (g_map[x - 1][y] == '1' && g_map_c[x - 1][y] == 0)
			dfs(x - 1, y);
		else if (g_map[x][y + 1] == '1' && g_map_c[x][y + 1] == 0)
			dfs(x, y + 1);
		else if (g_map[x][y - 1] == '1' && g_map_c[x][y - 1] == 0)
			dfs(x, y - 1);
		else
			back(x, y);
		break ;
	}
	return ;
}
