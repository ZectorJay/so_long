/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 06:45:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/09 21:55:42 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_all *all)
{
	size_t i;
	int j;
	int len;

	len = ft_strlen(all->map[0]);
	i = -1;
	while (all->map[++i])
	{
		j = -1;
		while (++j < len)
		{
			if (all->map[i][j] == '1')
				paint_square(all, j * TEXTURE_SIZE,
				i * TEXTURE_SIZE, &all->walls);
			else if (all->map[i][j] == '0')
				paint_square(all, j * TEXTURE_SIZE,
				i * TEXTURE_SIZE, &all->floor);
			else if (all->map[i][j] == 'C')
			{
				paint_square(all, j * TEXTURE_SIZE,
				i * TEXTURE_SIZE, &all->floor);
				paint_collectable(all, j * TEXTURE_SIZE, i * TEXTURE_SIZE);
			}
			else if (all->map[i][j] == 'E')
			{
				paint_square(all, j * TEXTURE_SIZE,
				i * TEXTURE_SIZE, &all->floor);
				paint_square(all, j * TEXTURE_SIZE,
				i * TEXTURE_SIZE, &all->exit);
			}
			if (all->map[i][j] == 'P' && all->player.pos_x == -1)
			{
				paint_square(all, j * TEXTURE_SIZE,
				i * TEXTURE_SIZE, &all->floor);
				all->player.pos_y = (float)(i * TEXTURE_SIZE);
				all->player.pos_x = (float)(j * TEXTURE_SIZE);
				all->player.old_pos_y = (float)(i * TEXTURE_SIZE);
				all->player.old_pos_x = (float)(j * TEXTURE_SIZE);
				paint_player(all);
			}
		}
	}
}

static void		fix_params(t_all *all, int *number, int flag)
{
	if (number)
		*(int*)number = (int)(-1 * (RAYS / 2));
	if (flag)
	{
		all->end_counter = (int)(RAYS / 2) + 1;
	}
	all->player.old_pos_x = (all->player.pos_x + PLAYER_SCALE);
	all->player.old_pos_y = (all->player.pos_y + PLAYER_SCALE);
	all->calc_cos = cos(all->player.rotate - (FIX_ANGLE * all->end_counter));
	all->calc_sin = sin(all->player.rotate - (FIX_ANGLE * all->end_counter));
}



void	make_flashlight(t_all *all)
{
	int		counter;
	int		number;
	int		color = 0xDDF9FC9A;
	
	counter = 360;
	fix_params(all, &number, 1);
	while (counter)
	{
		all->player.old_pos_x -= all->calc_cos;
		all->player.old_pos_y -= all->calc_sin;
		my_pixel_put(&all->flashlight,
			all->player.old_pos_x + (RES_X / 2 - all->player.pos_x),
			all->player.old_pos_y + (RES_Y / 2 - all->player.pos_y),
			color);
		if (all->player.old_pos_x <= 0 || all->player.old_pos_x > RES_X ||
		all->player.old_pos_y <= 0 || all->player.old_pos_y > RES_Y)
		{
			all->end_counter--;
			fix_params(all, 0, 0);
			counter--;
			color = 0xDDF9FC9A;
		}
	}
}



void			player_angle(t_all *all)
{
	float	len;
	int		number;

	fix_params(all, &number, 1);
	while (all->map[Y_STOP][X_STOP] != '1' && (len += 0.1) > 0)
	{
		all->player.old_pos_x -= all->calc_cos;
		all->player.old_pos_y -= all->calc_sin;
		my_pixel_put(&all->flashlight,
			all->player.old_pos_x + (RES_X / 2 - all->player.pos_x),
			all->player.old_pos_y + (RES_Y / 2 - all->player.pos_y),
			0xDDF9FC9A );
		if (all->map[Y_STOP][X_STOP] == '1')
		{
			if (all->end_counter > number)
				all->end_counter--;
			else
				break ;
			fix_params(all, 0, 0);
		}
	}
}