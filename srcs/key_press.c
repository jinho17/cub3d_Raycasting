/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:09:03 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 13:33:47 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_right(int key)
{
	if (key == KEY_RIGHT)
	{
		g_old_dir_x = g_info.dir.x;
		g_info.dir.x = g_info.dir.x * cos(-g_info.rot_speed)
						- g_info.dir.y * sin(-g_info.rot_speed);
		g_info.dir.y = g_old_dir_x * sin(-g_info.rot_speed)
						+ g_info.dir.y * cos(-g_info.rot_speed);
		g_old_plane_x = g_info.plane.x;
		g_info.plane.x = g_info.plane.x * cos(-g_info.rot_speed)
						- g_info.plane.y * sin(-g_info.rot_speed);
		g_info.plane.y = g_old_plane_x * sin(-g_info.rot_speed)
						+ g_info.plane.y * cos(-g_info.rot_speed);
	}
}

void	turn(int key)
{
	turn_right(key);
	if (key == KEY_LEFT)
	{
		g_old_dir_x = g_info.dir.x;
		g_info.dir.x = g_info.dir.x * cos(g_info.rot_speed)
						- g_info.dir.y * sin(g_info.rot_speed);
		g_info.dir.y = g_old_dir_x * sin(g_info.rot_speed)
						+ g_info.dir.y * cos(g_info.rot_speed);
		g_old_plane_x = g_info.plane.x;
		g_info.plane.x = g_info.plane.x * cos(g_info.rot_speed)
						- g_info.plane.y * sin(g_info.rot_speed);
		g_info.plane.y = g_old_plane_x * sin(g_info.rot_speed)
						+ g_info.plane.y * cos(g_info.rot_speed);
	}
}

void	forward_backword(int key)
{
	if (key == KEY_W)
	{
		if (g_map[(int)(g_info.pos.x + g_info.dir.x * g_info.move_speed)]
			[(int)g_info.pos.y] == '0')
			g_info.pos.x += g_info.dir.x * g_info.move_speed;
		if (g_map[(int)(g_info.pos.x)]
			[(int)(g_info.pos.y + g_info.dir.y * g_info.move_speed)] == '0')
			g_info.pos.y += g_info.dir.y * g_info.move_speed;
	}
	if (key == KEY_S)
	{
		if (g_map[(int)(g_info.pos.x - g_info.dir.x * g_info.move_speed)]
			[(int)g_info.pos.y] == '0')
			g_info.pos.x -= g_info.dir.x * g_info.move_speed;
		if (g_map[(int)(g_info.pos.x)]
			[(int)(g_info.pos.y - g_info.dir.y * g_info.move_speed)] == '0')
			g_info.pos.y -= g_info.dir.y * g_info.move_speed;
	}
}

void	move(int key)
{
	forward_backword(key);
	if (key == KEY_A)
	{
		if (g_map[(int)(g_info.pos.x - g_info.dir.y * g_info.move_speed)]
			[(int)g_info.pos.y] == '0')
			g_info.pos.x -= g_info.dir.y * g_info.move_speed;
		if (g_map[(int)(g_info.pos.x)]
			[(int)(g_info.pos.y + g_info.dir.x * g_info.move_speed)] == '0')
			g_info.pos.y += g_info.dir.x * g_info.move_speed;
	}
	if (key == KEY_D)
	{
		if (g_map[(int)(g_info.pos.x + g_info.dir.y * g_info.move_speed)]
			[(int)g_info.pos.y] == '0')
			g_info.pos.x += g_info.dir.y * g_info.move_speed;
		if (g_map[(int)(g_info.pos.x)]
			[(int)(g_info.pos.y - g_info.dir.x * g_info.move_speed)] == '0')
			g_info.pos.y -= g_info.dir.x * g_info.move_speed;
	}
}

int		key_press(int key)
{
	if (key == KEY_ESC)
		exit(0);
	mlx_clear_window(g_mlx, g_window);
	move(key);
	turn(key);
	return (0);
}
