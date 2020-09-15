/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 17:06:45 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 14:21:38 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	var_free(void)
{
	int i;

	i = 0;
	while (i < g_screen.height)
		free(g_buf[i++]);
	free(g_buf);
	i = 0;
	while (i < 5)
		free(g_texture[i++]);
	free(g_texture);
	i = 0;
	while (i < 5)
	{
		free(g_tex_path[i].path);
		i++;
	}
	mlx_destroy_image(g_mlx, g_img.image);
	free(g_sp.z_buffer);
	free(g_sprite);
	free(g_sp.order);
	free(g_sp.distance);
	mlx_destroy_window(g_mlx, g_window);
}

int		cub3d_exit(void)
{
	exit(0);
	return (0);
}

void	set_sprite(void)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < g_m.height)
	{
		x = 0;
		while (x < g_m.width)
		{
			if (g_map[x][y] == '2')
			{
				g_sprite[i].x = x + 0.5f;
				g_sprite[i].y = y + 0.5f;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	setting(int argc, char *argv[])
{
	int	i;

	g_info.move_speed = 1;
	g_info.rot_speed = 0.05;
	g_tex.height = 64;
	g_tex.width = 64;
	g_sp.num = 0;
	g_save_op = (argc == 3 &&
					ft_strncmp(argv[argc - 1], "--save", 6) == 0) ? 1 : 0;
	g_mlx = mlx_init();
	i = 0;
	while (i < 8)
		g_id[i++][0] = 0;
}

int		main(int argc, char *argv[])
{
	setting(argc, argv);
	if (0 > map_file_open(argc, argv))
		exit(1);
	if (0 > map_check(0, 0))
	{
		ft_putstr_fd("Error\nInvalid map format.\n", 1);
		exit(1);
	}
	if (0 > var_malloc())
		exit(1);
	set_sprite();
	g_img.image = mlx_new_image(g_mlx, g_screen.width, g_screen.height);
	g_img.data = (int *)mlx_get_data_addr(
			g_img.image, &g_img.bpp, &g_img.size_lin, &g_img.endian);
	if (0 > load_texture())
		exit(1);
	init_pos_dir();
	g_window = mlx_new_window(g_mlx, g_screen.width, g_screen.height, "cub3D");
	mlx_hook(g_window, KEY_PRESS_MASK, (1L << 0), key_press, 0);
	mlx_hook(g_window, KEY_EXIT_MASK, 0, cub3d_exit, 0);
	mlx_loop_hook(g_mlx, loop_manager, 0);
	mlx_loop(g_mlx);
	var_free();
	return (0);
}
