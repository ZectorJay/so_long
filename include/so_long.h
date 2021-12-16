/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:31:41 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/10 18:58:38 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "fcntl.h"
# include <math.h>
# include <pthread.h>

/* DONT FORGET TO REMOVE ALTERNATIVE CONTROL */

# define ALTERNATIVE_CONTROL 0	/* 1 or 0 */

# define RES_X			1560
# define RES_Y			1200

/* MAY BE GONNA ADD DEPENDACE FROM RESOLUTION */
# define TEXTURE_SIZE	(int)(RES_X / 15)		/* in pixels */

# define MOVEMENT_SPEED TEXTURE_SIZE/1.3
# define ROTATION_SPEED	3
# define RAYS			1000					/* flashlight */

# define PLAYER_SCALE	(int)(0)
# define ANGLE			(float)M_PI * 2
# define FIX_ANGLE		(float)(ANGLE/RAYS)
# define X_STOP			(int)(all->player.old_pos_x/TEXTURE_SIZE)
# define Y_STOP			(int)(all->player.old_pos_y/TEXTURE_SIZE)
# define XSTOP			(int)(all->player.pos_x + PLAYER_SCALE)/TEXTURE_SIZE
# define YSTOP			(int)(all->player.pos_y + PLAYER_SCALE)/TEXTURE_SIZE


# define RESET			"\033[0m"
# define BLACK			"\033[30m"	  		/* Black */
# define RED			"\033[31m"			/* Red */
# define GREEN			"\033[32m"			/* Green */
# define YELLOW			"\033[33m"			/* Yellow */
# define BLUE			"\033[34m"			/* Blue */
# define MAGENTA		"\033[35m"			/* Magenta */
# define CYAN			"\033[36m"			/* Cyan */
# define WHITE			"\033[37m"			/* White */
# define BOLDBLACK		"\033[1m\033[30m"	/* Bold Black */
# define BOLDRED		"\033[1m\033[31m"	/* Bold Red */
# define BOLDGREEN		"\033[1m\033[32m"	/* Bold Green */
# define BOLDYELLOW		"\033[1m\033[33m"	/* Bold Yellow */
# define BOLDBLUE		"\033[1m\033[34m"	/* Bold Blue */
# define BOLDMAGENTA	"\033[1m\033[35m"	/* Bold Magenta */
# define BOLDCYAN		"\033[1m\033[36m"	/* Bold Cyan */
# define BOLDWHITE		"\033[1m\033[37m"	/* Bold White */

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_mlx
{
	void	*con;
	void	*window;
	int		res_x;
	int		res_y;
}			t_mlx;

typedef struct		s_texture
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	char			*path;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				color_mass[TEXTURE_SIZE][TEXTURE_SIZE];
	int				*color_row;
	float			res;
	float			fix_res_y;
}					t_texture;

typedef struct s_game
{
	int		collectable;
	int		steps;
}			t_game;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	old_pos_x;
	float	old_pos_y;
	float	rotate;
	int		press_w;
	int		press_a;
	int		press_s;
	int		press_d;
	int		pres_jump;
	int		press_rotate;
	int		movement_speed;
}			t_player;

typedef struct s_all
{
	t_data			img;
	t_mlx			mlx;
	t_texture		background;
	pthread_t		thread;
	t_texture		flashlight;
	t_texture		sky;
	t_texture		tmp_player; /* временная затычка */

	t_texture		walls;
	t_texture		floor;
	t_texture		character;
	t_texture		exit;
	t_texture		collect;
	t_texture		*enemy;
	t_player		player;
	char			**map;
	size_t			counter;
	int				jump_flag;
	float			cos_table[RAYS];
	float			calc_cos;
	float			calc_sin;
	int				end_counter;
}					t_all;

void	error_message(char *message, t_all *all);
void	check_args(t_all *all, char *argv);
void	my_pixel_put(t_texture *data, int x, int y, int color);
void	fill_background(t_all *all);
int		check_key(int key, t_all *all);
void	check_movement(t_all *all);
int		key_release(int key, t_all *all);
void	get_color(t_texture *data);
/* Временный костыль */
void	paint_square(t_all *all, int x, int y, t_texture *img);
int		get_next_line(int fd, char **line);
void	find_player(t_all *all);
void	print_map(t_all *all);
// void	draw_angle(t_all *all);
void	player_angle(t_all *all);
void	rotate_player(t_all *all);
void	check_movement2(t_all *all);
void	paint_player(t_all *all);
void	paint_collectable(t_all *all, int x, int y);
void	make_flashlight(t_all *all);

#endif