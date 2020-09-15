/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:54:53 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/10 18:06:55 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_color(int x)
{
	int y;

	y = g_ray.draw_start;
	while (y < g_ray.draw_end)
	{
		g_ray.tex.y = (int)g_ray.tex_pos & (g_tex.height - 1);
		g_ray.tex_pos += g_ray.step;
		g_ray.color = g_texture[g_ray.side]
					[g_tex.height * g_ray.tex.y + g_ray.tex.x];
		g_buf[y][x] = g_ray.color;
		y++;
	}
	y = 0;
	while (y < g_ray.draw_start)
	{
		g_buf[y][x] = g_ceilling_color;
		y++;
	}
	y = g_ray.draw_end;
	while (y < g_screen.height && y >= 0)
	{
		g_buf[y][x] = g_floor_color;
		y++;
	}
}

void	wall_texture(void)
{
	if (g_ray.side == 1 || g_ray.side == 2)
		g_ray.wall_x = g_info.pos.y + g_ray.perp_wall_dist * g_ray.ray_dir.y;
	else if (g_ray.side == 3 || g_ray.side == 4)
		g_ray.wall_x = g_info.pos.x + g_ray.perp_wall_dist * g_ray.ray_dir.x;
	g_ray.wall_x -= floor((g_ray.wall_x));
	g_ray.tex.x = (int)(g_ray.wall_x * ((double)g_tex.width));
	if ((g_ray.side == 1 || g_ray.side == 2) && g_ray.ray_dir.x > 0)
		g_ray.tex.x = g_tex.width - g_ray.tex.x - 1;
	else if ((g_ray.side == 3 || g_ray.side == 4) && g_ray.ray_dir.y < 0)
		g_ray.tex.x = g_tex.width - g_ray.tex.x - 1;
	g_ray.step = 1.0 * g_tex.height / g_ray.line_height;
	g_ray.tex_pos = (g_ray.draw_start - g_screen.height / 2 +
					g_ray.line_height / 2) * g_ray.step;
}

void	draw_start_end(void)
{
	if (g_ray.side == 1 || g_ray.side == 2)
	{
		g_ray.perp_wall_dist = (g_ray.map.x - g_info.pos.x +
				(1 - g_ray.step_.x) / 2) / g_ray.ray_dir.x;
		if (g_ray.perp_wall_dist == 0)
		{
			g_ray.perp_wall_dist = 0.1 / -g_ray.ray_dir.x;
		}
	}
	else if (g_ray.side == 3 || g_ray.side == 4)
	{
		g_ray.perp_wall_dist = (g_ray.map.y - g_info.pos.y +
					(1 - g_ray.step_.y) / 2) / g_ray.ray_dir.y;
		if (g_ray.perp_wall_dist == 0)
		{
			g_ray.perp_wall_dist = 0.1 / -g_ray.ray_dir.y;
		}
	}
	g_ray.line_height = (int)(g_screen.height / g_ray.perp_wall_dist);
	g_ray.draw_start = -1 * g_ray.line_height / 2 + g_screen.height / 2;
	if (g_ray.draw_start < 0)
		g_ray.draw_start = 0;
	g_ray.draw_end = g_ray.line_height / 2 + g_screen.height / 2;
	if (g_ray.draw_end >= g_screen.height)
		g_ray.draw_end = g_screen.height - 1;
}

void	hit(void)
{
	while (g_ray.hit == 0)
	{
		if (g_ray.side_dist.x < g_ray.side_dist.y)
		{
			g_ray.side_dist.x += g_ray.delta_dist.x;
			g_ray.map.x += g_ray.step_.x;
			g_ray.side = (g_ray.step_.x == -1) ? 1 : 2;
		}
		else
		{
			g_ray.side_dist.y += g_ray.delta_dist.y;
			g_ray.map.y += g_ray.step_.y;
			g_ray.side = (g_ray.step_.y == -1) ? 3 : 4;
		}
		if (g_map[g_ray.map.x][g_ray.map.y] == '1')
			g_ray.hit = 1;
	}
}

void	step_n_sidedist(void)
{
	if (g_ray.ray_dir.x < 0)
	{
		g_ray.step_.x = -1;
		g_ray.side_dist.x = (g_info.pos.x - g_ray.map.x) * g_ray.delta_dist.x;
	}
	else
	{
		g_ray.step_.x = 1;
		g_ray.side_dist.x = (g_ray.map.x + 1.0 - g_info.pos.x)
							* g_ray.delta_dist.x;
	}
	if (g_ray.ray_dir.y < 0)
	{
		g_ray.step_.y = -1;
		g_ray.side_dist.y = (g_info.pos.y - g_ray.map.y) * g_ray.delta_dist.y;
	}
	else
	{
		g_ray.step_.y = 1;
		g_ray.side_dist.y = (g_ray.map.y + 1.0 - g_info.pos.y)
							* g_ray.delta_dist.y;
	}
}
