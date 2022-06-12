/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:24:18 by tratanat          #+#    #+#             */
/*   Updated: 2022/06/12 15:05:52 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"

# define WWIDTH 1600
# define WHEIGHT 900
# define MWIDTH 6
# define MHEIGHT 5
# define MAPSIZE 150

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	side_dx;
	double	side_dy;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		count_x;
	int		count_y;
	double	init_y;
	double	init_x;
	double	tex_offset;
	double	distance;
}	t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		linelen;
	int		endian;
}	t_data;

typedef struct s_map
{
	int	**map;
	int	height;
	int	width;
}	t_map;

typedef struct s_minimap
{
	int	scale;
	int	pos_x;
	int	pos_y;
}	t_minimap;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	cam_x;
	double	cam_y;
	double	movespeed;
	double	rot_speed;
}	t_player;

typedef struct s_input
{
	int	mouse_pressed;
	int	rmouse_pressed;
	int	mouse_x;
	int	mouse_y;
}	t_input;

typedef struct s_texture
{
	int		width;
	int		height;
	t_data	*img;
}	t_texture;

typedef struct s_gamevars
{
	int			scale;
	void		*mlx;
	void		*mlx_win;
	t_data		*img;
	t_map		map;
	t_player	*player;
	t_minimap	*minimap;
	t_input		*input;
	t_texture	*textures;
	int			tex_count;
}	t_gamevars;

void	draw_grid(t_gamevars *gamevars, int scale, int off_h, int off_w);
void	draw_player(t_gamevars *gamevars, int scale, int off_h, int off_w);
int		drawframe(t_gamevars *gamevars);
void	draw_map(t_gamevars *gamevars);

// Initializations
void	inithooks(void *mlx_win, t_gamevars *gamevars);
void	init_player(t_player *player);
int		**init_map(void);
void	init_minimap(t_minimap *minimap);

// Input and player movement
int		mousectl(int button, int x, int y, t_gamevars *gamevars);
int		mouserel(int button, int x, int y, t_gamevars *gamevars);
int		mouserot(int x, int y, t_gamevars *gamevars);
int		keymod(int keycode, t_gamevars *gamevars);
void	player_move_ad(t_gamevars *gamevars, int fwd);
void	player_move_ws(t_gamevars *gamevars, int fwd);
void	player_rotate(t_gamevars *gamevars, int dir);

// Camera calculations
void	calc_ray(t_gamevars *gamevars);
double	wall_distance(t_gamevars *gamevars, t_ray *ray);
void	calc_sidedist(t_gamevars *gamevars, t_ray *ray);
double	dda(t_gamevars *gamevars, t_ray *ray);
double	get_distance(t_gamevars *gamevars, t_ray *ray, int side);

// Draw calls
void	pixel_put(t_data *data, int x, int y, int color);
void	draw_wall_col(t_gamevars *gamevars, int x, t_ray *ray);
void	draw_ceiling(t_gamevars *gamevars);
void	draw_floor(t_gamevars *gamevars);

// Texture handling
int		texture_load(t_gamevars *gamevars);

// Cleanup
int		end_win(t_gamevars *gamevars);

#endif