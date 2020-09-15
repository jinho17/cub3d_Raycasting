/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 16:52:44 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/09 17:00:06 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		**int2p_malloc(int x, int y, int i, int j)
{
	int **rtn;

	if (!(rtn = (int **)malloc(sizeof(int *) * y)))
	{
		ft_putstr_fd("Error\n", 1);
		return (NULL);
	}
	while (i < y)
	{
		if (!(rtn[i] = (int *)malloc(sizeof(int) * x)))
		{
			ft_putstr_fd("Error\n", 1);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
			rtn[i][j++] = 0;
		i++;
	}
	return (rtn);
}

int		var_malloc(void)
{
	if ((g_buf = int2p_malloc(g_screen.width, g_screen.height, 0, 0)) == NULL)
		return (-1);
	if ((g_texture = int2p_malloc(g_tex.height * g_tex.width, 5, 0, 0)) == NULL)
		return (-1);
	if (!(g_sp.z_buffer = (double *)malloc(sizeof(double) * g_screen.width)))
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	if (!(g_sprite = (t_sprite *)malloc(sizeof(t_sprite) * g_sp.num)))
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	if (!(g_sp.order = (int *)malloc(sizeof(int) * g_sp.num)))
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	if (!(g_sp.distance = (double *)malloc(sizeof(double) * g_sp.num)))
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	return (0);
}
