/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 11:28:08 by jinkim            #+#    #+#             */
/*   Updated: 2020/09/11 14:31:34 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "../libft/libft.h"

# define KEY_PRESS_MASK 2
# define KEY_EXIT_MASK 17
# define R_WIDTH 1600
# define R_HEIGHT 900
# define KEY_W 0xd
# define KEY_S 0x1
# define KEY_A 0x0
# define KEY_D 0x2
# define KEY_ESC 0x35
# define KEY_UP 0x7c
# define KEY_DOWN 0x7d
# define KEY_RIGHT 0x7c
# define KEY_LEFT 0x7b

typedef struct	s_width_height
{
	int			width;
	int			height;
}				t_wh;
t_wh g_screen;
t_wh g_tex;

typedef struct	s_path
{
	char		*path;
}				t_path;
t_path			g_tex_path[5];

typedef struct	s_map
{
	int			width;
	int			height;
	int			check_pos;
}				t_map;
t_map g_m;

typedef struct	s_dfs
{
	int			x;
	int			y;
	int			width;
	int			height;
}				t_dfs;
t_dfs g_dfs;

typedef struct	s_double_xy
{
	double		x;
	double		y;
}				t_double_xy;

typedef struct	s_int_xy
{
	int			x;
	int			y;
}				t_int_xy;

typedef struct	s_info
{
	t_double_xy	pos;
	t_double_xy	dir;
	t_double_xy	plane;
	double		move_speed;
	double		rot_speed;
}				t_info;
t_info g_info;

typedef struct	s_ray
{
	double		camera_x;
	t_double_xy ray_dir;
	t_int_xy	map;
	t_double_xy	side_dist;
	t_double_xy	delta_dist;
	double		perp_wall_dist;
	t_int_xy	step_;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_int_xy	tex;
	double		step;
	double		tex_pos;
	int			color;
}				t_ray;
t_ray g_ray;

typedef struct	s_image
{
	void		*image;
	int			*data;
	int			size_lin;
	int			bpp;
	int			endian;
	int			xpm_x;
	int			xpm_y;
}				t_image;
t_image g_img;

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;
t_sprite *g_sprite;

typedef struct	s_sprite_ray
{
	int			num;
	double		*z_buffer;
	int			*order;
	double		*distance;
	t_double_xy	xy;
	double		inv_det;
	t_double_xy	transform;
	int			screen_x;
	int			u_div;
	int			v_div;
	double		v_move;
	int			v_move_screen;
	t_wh		sprite;
	t_int_xy	draw_start;
	t_int_xy	draw_end;
	int			stripe;
}				t_sprite_ray;
t_sprite_ray g_sp;

int				g_id[8][1];
int				g_floor_color;
int				g_ceilling_color;
char			g_map[2048][2048];
int				g_map_c[2048][2048];
int				**g_texture;
void			*g_mlx;
void			*g_window;
double			g_old_plane_x;
double			g_old_dir_x;
int				**g_buf;
int				g_save_op;

/*
** main.c
*/
void			setting(int argc, char *argv[]);
void			set_sprite(void);
int				cub3d_exit(void);
void			var_free(void);

/*
**  var_malloc.c
*/
int				var_malloc(void);
int				**int2p_malloc(int x, int y, int i, int j);

/*
** load_texture.c
*/
int				load_texture(void);
int				load_image(int *texture, char *path, t_image *img);

/*
** init_pos_dir.c
*/
void			init_pos_dir(void);
void			north_south(int x, int y);
void			east_west(int x, int y);

/*
** save_bmp.c
*/
int				save_bmp(void);
void			bmp_header(int fd, int size);
void			write_bmp(int fd);

/*
** map_file_open.c
*/
int				map_file_open(int argc, char *argv[]);
int				argc_error_check(int argc);
int				file_open(int fd);
int				get_next_line(int fd, int *fd_size);

/*
** get_map_info.c
*/
int				get_map_info(char *line);
int				map_info(char *line, char *id, char *info);
int				g_id_check(char *id);
int				resolution(char *info);
int				get_tex_path(char *id, char *info);

/*
** get_map_info2.c
*/
int				fc_color(char *id, char *info);
void			fc_free(char **color_str);
int				init_map(char *line);

/*
** get_map_info_error.c
*/
int				g_id_error(void);
int				resolution_error(char *info, int space);
int				fc_error(char *info, char **color_str, int *color);

/*
** map_check.c
*/
int				map_check(int x, int y);
int				map_edge_check(void);
int				map_zero_check(int x, int y);
int				zero_check(int x, int y);
int				zero_check_y(int x, int y);

/*
** dfs.c
*/
void			dfs(int x, int y);
void			back(int x, int y);

/*
** key_press.c
*/
int				key_press(int key);
void			move(int key);
void			forward_backward(int key);
void			turn(int key);
void			turn_right(int key);

/*
** loop_manager.c
*/
int				loop_manager(void);
void			init_ray(int x);
void			wall_raycasting(void);
void			sprite_raycasting(void);
void			draw(void);

/*
** wall_raycasting.c
*/
void			step_n_sidedist(void);
void			hit(void);
void			draw_start_end(void);
void			wall_texture(void);
void			get_color(int x);

/*
** sprite_raycasting.c
*/
void			sort_sprite(void);
void			sprite_height(int i);
void			sprite_width(void);
void			stripe(int d);

#endif
