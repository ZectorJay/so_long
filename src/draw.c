/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 06:19:36 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/09 21:12:19 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_pixel_put(t_texture *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	get_color(t_texture *data)
{
	float	x;
	float	y;
	char	*dst;
	int		counter;
	int		counter2;
	float	scale2;
	float	scale;
	
	scale = (float)data->width / (float)TEXTURE_SIZE;
	scale2 = (float)data->height / (float)TEXTURE_SIZE;
	x = 0;
	counter = 0;
	counter2 = 0;
	while ((int)(x) < data->width)
	{
		y = 0;
		counter2 = -1;
		while ((int)y   < data->height)
		{
			++counter2;
			dst = (data->addr + ((int)y * data->line_length +
			(int)x * (data->bits_per_pixel / 8)));
			data->color_mass[counter][counter2] = *(unsigned int*)dst;
			y += scale2;
		}
		counter++;
		x += scale;
	}
	data->color_mass[counter][0] = 0;
}

void	fill_background(t_all *all)
{
	size_t i;
	size_t j;

	i = -1;
	j = -1;
	all->background.img = mlx_new_image(all->mlx.con, RES_X, RES_Y);
	while (++i < all->counter)
	{
		j = -1;
		while (++j < ft_strlen(all->map[0]))
		{
			if (all->map[i][j] == '1')
				;
		}
	}
}

void	paint_player(t_all *all)
{
	int first;
	int second;

	first = -1;
	second = 0;
	while (++first < TEXTURE_SIZE)
	{
		second = -1;
		while (++second < TEXTURE_SIZE)
		{
			my_pixel_put(&all->tmp_player, second, first, 
			all->character.color_mass[second][first]);
		}
	}
}

void	paint_collectable(t_all *all, int x, int y)
{
	int first;
	int second;
	int old;

	x += (TEXTURE_SIZE / 4);
	y += (TEXTURE_SIZE / 4);
	old = x;
	first = -1;
	second = 0;
	while (++first < TEXTURE_SIZE)
	{
		++first;
		second = -1;
		x = old;
		while (++second < TEXTURE_SIZE)
		{
			++second;
			if (all->collect.color_mass[second][first] > 0)
				my_pixel_put(&all->background, x, y, 
				all->collect.color_mass[second][first]);
			x++;
		}
		y++;
	}
}

void	paint_square(t_all *all, int x, int y, t_texture *img)
{
	int first;
	int second;
	int old;

	old = x;
	first = -1;
	second = 0;
	while (++first < TEXTURE_SIZE)
	{
		second = -1;
		x = old;
		while (++second < TEXTURE_SIZE)
		{
			if (img && img->color_mass[second][first] > 0)
				my_pixel_put(&all->background, x, y, img->color_mass[second][first]);
			x++;
		}
		y++;
	}
}