/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:44:06 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 13:07:38 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		fc_error(char *info, char **color_str, int *color)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(info))
	{
		if ((info[i] < '0' || info[i] > '9') && info[i] != ',')
			return (-1);
		i++;
	}
	i = 0;
	while (color_str[i] != 0)
		i++;
	if (i != 3)
		return (-1);
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(color_str[i]);
		if (color[i] < 0 || color[i] > 255)
			return (-1);
		i++;
	}
	return (0);
}

int		resolution_error(char *info, int space)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(info))
	{
		if (!((info[i] >= '0' && info[i] <= '9') || info[i] == ' '))
			return (-1);
		i++;
	}
	while (info[space] == ' ')
		space++;
	while (space < (int)ft_strlen(info) && info[space] >= '0'
			&& info[space] <= '9')
		space++;
	if (space != (int)ft_strlen(info))
		return (-1);
	return (0);
}

int		g_id_error(void)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (g_id[i][0] != 1)
			return (-1);
		i++;
	}
	return (0);
}
