/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 11:52:57 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 11:53:40 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		load_image(int *texture, char *path, t_image *img)
{
	int x;
	int y;

	if (NULL == (img->image =
				mlx_xpm_file_to_image(g_mlx, path, &img->xpm_x, &img->xpm_y)))
	{
		ft_putstr_fd("Error\nInvalid texture path!\n", 1);
		return (-1);
	}
	img->data = (int *)mlx_get_data_addr(
						img->image, &img->bpp, &img->size_lin, &img->endian);
	y = 0;
	while (y < img->xpm_y)
	{
		x = 0;
		while (x < img->xpm_x)
		{
			texture[img->xpm_x * y + x] = img->data[img->xpm_x * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(g_mlx, img->image);
	return (0);
}

int		load_texture(void)
{
	t_image img;
	int		i;

	i = 0;
	while (i < 5)
	{
		if (0 > load_image(g_texture[i], g_tex_path[i].path, &img))
			return (-1);
		i++;
	}
	return (0);
}
