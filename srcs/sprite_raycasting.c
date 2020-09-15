/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 10:41:20 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 14:12:55 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stripe(int d)
{
	int y;

	g_sp.stripe = g_sp.draw_start.x;
	while (g_sp.stripe < g_sp.draw_end.x)
	{
		g_ray.tex.x = (int)(256 * (g_sp.stripe - (-1 * g_sp.sprite.width / 2 +
					g_sp.screen_x)) * g_tex.width / g_sp.sprite.width) / 256;
		if (g_sp.transform.y > 0 && g_sp.stripe > 0 && g_sp.stripe
			< g_screen.width && g_sp.transform.y < g_sp.z_buffer[g_sp.stripe])
		{
			y = g_sp.draw_start.y;
			while (y < g_sp.draw_end.y)
			{
				d = (y - g_sp.v_move_screen) * 256 - g_screen.height * 128
					+ g_sp.sprite.height * 128;
				g_ray.tex.y = ((d * g_tex.height) / g_sp.sprite.height) / 256;
				g_ray.color = g_texture[0][
								g_tex.width * g_ray.tex.y + g_ray.tex.x];
				if ((g_ray.color & 0x00ffffff) != 0)
					g_buf[y][g_sp.stripe] = g_ray.color;
				y++;
			}
		}
		g_sp.stripe++;
	}
}

void	sprite_width(void)
{
	g_sp.sprite.width = (int)(fabs(g_screen.height / g_sp.transform.y)
								/ g_sp.u_div);
	g_sp.draw_start.x = -1 * g_sp.sprite.width / 2 + g_sp.screen_x;
	if (g_sp.draw_start.x < 0)
		g_sp.draw_start.x = 0;
	g_sp.draw_end.x = g_sp.sprite.width / 2 + g_sp.screen_x;
	if (g_sp.draw_end.x >= g_screen.width)
		g_sp.draw_end.x = g_screen.width - 1;
}

void	sprite_height(int i)
{
	g_sp.xy.x = g_sprite[g_sp.order[i]].x - g_info.pos.x;
	g_sp.xy.y = g_sprite[g_sp.order[i]].y - g_info.pos.y;
	g_sp.inv_det = 1.0 / (g_info.plane.x * g_info.dir.y -
					g_info.dir.x * g_info.plane.y);
	g_sp.transform.x = g_sp.inv_det *
						(g_info.dir.y * g_sp.xy.x - g_info.dir.x * g_sp.xy.y);
	g_sp.transform.y = g_sp.inv_det * (-1 * g_info.plane.y * g_sp.xy.x
										+ g_info.plane.x * g_sp.xy.y);
	g_sp.screen_x = (int)((g_screen.width / 2) *
					(1 + g_sp.transform.x / g_sp.transform.y));
	g_sp.v_move_screen = (int)(g_sp.v_move / g_sp.transform.y);
	g_sp.sprite.height = (int)(fabs(g_screen.height / g_sp.transform.y)
								/ g_sp.v_div);
	g_sp.draw_start.y = -1 * g_sp.sprite.height / 2
						+ g_screen.height / 2 + g_sp.v_move_screen;
	if (g_sp.draw_start.y < 0)
		g_sp.draw_start.y = 0;
	g_sp.draw_end.y = g_sp.sprite.height / 2 + g_screen.height / 2
						+ g_sp.v_move_screen;
	if (g_sp.draw_end.y >= g_screen.height)
		g_sp.draw_end.y = g_screen.height - 1;
}

void	sort_sprite(void)
{
	t_sprite	temp;
	int			i;
	int			j;
	int			max;

	i = 0;
	max = 0;
	while (i < g_sp.num - 1)
	{
		max = i;
		j = i + 1;
		while (j < g_sp.num)
		{
			if (g_sp.distance[j] > g_sp.distance[i])
				max = j;
			j++;
		}
		if (i != max)
		{
			temp = g_sprite[i];
			g_sprite[i] = g_sprite[max];
			g_sprite[max] = temp;
		}
		i++;
	}
}
