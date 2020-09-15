/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:54:09 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 13:54:48 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(void)
{
	int x;
	int y;

	y = 0;
	while (y < g_screen.height)
	{
		x = 0;
		while (x < g_screen.width)
		{
			g_img.data[y * g_screen.width + x] = g_buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g_mlx, g_window, g_img.image, 0, 0);
	if (g_save_op == 1)
		save_bmp();
}

void	sprite_raycasting(void)
{
	int i;

	i = 0;
	while (i < g_sp.num)
	{
		g_sp.order[i] = i;
		g_sp.distance[i] =
			(g_info.pos.x - g_sprite[i].x) * (g_info.pos.x - g_sprite[i].x)
			+ (g_info.pos.y - g_sprite[i].y) * (g_info.pos.y - g_sprite[i].y);
		i++;
	}
	sort_sprite();
	g_sp.u_div = 1;
	g_sp.v_div = 1;
	g_sp.v_move = 0.0;
	i = 0;
	while (i < g_sp.num)
	{
		sprite_height(i);
		sprite_width();
		stripe(0);
		i++;
	}
}

void	init_ray(int x)
{
	g_ray.camera_x = 2 * x / (double)g_screen.width - 1;
	g_ray.ray_dir.x = g_info.dir.x + g_info.plane.x * g_ray.camera_x;
	g_ray.ray_dir.y = g_info.dir.y + g_info.plane.y * g_ray.camera_x;
	g_ray.map.x = (int)g_info.pos.x;
	g_ray.map.y = (int)g_info.pos.y;
	g_ray.delta_dist.x = fabs(1 / g_ray.ray_dir.x);
	g_ray.delta_dist.y = fabs(1 / g_ray.ray_dir.y);
	g_ray.hit = 0;
	g_ray.step_.x = 0;
	g_ray.step_.y = 0;
}

void	wall_raycasting(void)
{
	int x;

	x = 0;
	while (x < g_screen.width)
	{
		init_ray(x);
		step_n_sidedist();
		hit();
		draw_start_end();
		wall_texture();
		get_color(x);
		g_sp.z_buffer[x] = g_ray.perp_wall_dist;
		x++;
	}
}

int		loop_manager(void)
{
	wall_raycasting();
	sprite_raycasting();
	draw();
	return (0);
}
