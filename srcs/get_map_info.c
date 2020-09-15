/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:52:02 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 12:59:00 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_tex_path(char *id, char *info)
{
	if (0 == ft_strncmp(id, "NO", 2))
		g_tex_path[1].path = ft_strdup(info);
	else if (0 == ft_strncmp(id, "SO", 2))
		g_tex_path[2].path = ft_strdup(info);
	else if (0 == ft_strncmp(id, "WE", 2))
		g_tex_path[3].path = ft_strdup(info);
	else if (0 == ft_strncmp(id, "EA", 2))
		g_tex_path[4].path = ft_strdup(info);
	else if (0 == ft_strncmp(id, "S", 2))
		g_tex_path[0].path = ft_strdup(info);
	return (0);
}

int		resolution(char *info)
{
	int		space;
	char	*width;
	char	*height;

	space = 0;
	while (info[space] != ' ')
		space++;
	width = ft_substr(info, 0, space);
	height = ft_substr(info, space + 1, ft_strlen(info) - space);
	if (0 > resolution_error(info, space))
		return (-1);
	g_screen.width = ft_atoi(width);
	g_screen.height = ft_atoi(height);
	free(width);
	free(height);
	if (g_screen.width <= 0 || g_screen.height <= 0)
		return (-1);
	if (g_screen.width > R_WIDTH)
		g_screen.width = R_WIDTH;
	if (g_screen.height > R_HEIGHT)
		g_screen.height = R_HEIGHT;
	return (0);
}

int		g_id_check(char *id)
{
	if (0 == ft_strncmp(id, "R", 2))
		g_id[0][0]++;
	else if (0 == ft_strncmp(id, "NO", 2))
		g_id[1][0]++;
	else if (0 == ft_strncmp(id, "SO", 2))
		g_id[2][0]++;
	else if (0 == ft_strncmp(id, "WE", 2))
		g_id[3][0]++;
	else if (0 == ft_strncmp(id, "EA", 2))
		g_id[4][0]++;
	else if (0 == ft_strncmp(id, "S", 2))
		g_id[5][0]++;
	else if (0 == ft_strncmp(id, "F", 2))
		g_id[6][0]++;
	else if (0 == ft_strncmp(id, "C", 2))
		g_id[7][0]++;
	else
	{
		if (0 > g_id_error())
			return (-1);
	}
	return (0);
}

int		map_info(char *line, char *id, char *info)
{
	if (0 > g_id_check(id))
		return (-1);
	if (0 == ft_strncmp(id, "R", 2))
	{
		if (0 > resolution(info))
			return (-1);
	}
	else if (0 == ft_strncmp(id, "NO", 2) || 0 == ft_strncmp(id, "SO", 2) ||
			0 == ft_strncmp(id, "WE", 2) || 0 == ft_strncmp(id, "EA", 2) ||
			0 == ft_strncmp(id, "S", 2))
	{
		if (0 > get_tex_path(id, info))
			return (-1);
	}
	else if (0 == ft_strncmp(id, "F", 2) || 0 == ft_strncmp(id, "C", 2))
	{
		if (0 > fc_color(id, info))
			return (-1);
	}
	else
	{
		if (0 > init_map(line))
			return (-1);
	}
	return (0);
}

int		get_map_info(char *line)
{
	char	*info;
	char	*id;
	int		id_len;

	id_len = 0;
	if (line[1] == ' ')
		id_len = 1;
	else if (line[2] == ' ')
		id_len = 2;
	id = ft_substr(line, 0, id_len);
	while (line[id_len] == ' ')
		id_len++;
	info = ft_substr(line, id_len, ft_strlen(line) - id_len + 1);
	if (0 > map_info(line, id, info))
	{
		free(id);
		free(info);
		return (-1);
	}
	free(id);
	free(info);
	return (0);
}
