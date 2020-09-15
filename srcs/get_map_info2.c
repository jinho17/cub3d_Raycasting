/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 13:06:48 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 12:59:49 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_map(char *line)
{
	int		i;
	int		map_idx;

	i = 0;
	map_idx = 0;
	while (line[i] != 0)
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' &&
				line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
				line[i] != 'W' && line[i] != ' ')
			return (-1);
		else
			g_map[g_m.width][map_idx++] = line[i];
		i++;
	}
	g_map[g_m.width][map_idx] = '\0';
	if (g_m.height < (int)ft_strlen(line))
		g_m.height = (int)ft_strlen(line);
	g_m.width++;
	return (0);
}

void	fc_free(char **color_str)
{
	int i;

	i = 0;
	while (color_str[i] != 0)
		free(color_str[i++]);
	free(color_str);
}

int		fc_color(char *id, char *info)
{
	int		*color;
	char	**color_str;

	color_str = ft_split(info, ',');
	if (!(color = (int *)malloc(sizeof(int) * 3)))
		return (-1);
	if (0 > fc_error(info, color_str, color))
	{
		fc_free(color_str);
		return (-1);
	}
	if (0 == ft_strncmp(id, "F", 2))
		g_floor_color = (color[0] << 16) + (color[1] << 8) + (color[2]);
	else if (0 == ft_strncmp(id, "C", 2))
		g_ceilling_color = (color[0] << 16) + (color[1] << 8) + (color[2]);
	fc_free(color_str);
	free(color);
	return (0);
}
