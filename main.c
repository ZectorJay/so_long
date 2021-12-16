/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 23:27:40 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/10 18:59:27 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void fill_structure(t_all *all)
{
	all->player.pos_x = -1;
	all->player.press_w = 0;
	all->player.press_a = 0;
	all->player.press_s = 0;
	all->player.press_d = 0;
	all->player.press_rotate = 0;
	all->player.rotate = 0;
	all->player.pres_jump = -1;
	all->player.movement_speed = MOVEMENT_SPEED;
	all->jump_flag = 0;
	int max;
	if (RES_Y > RES_X)
		max = RES_Y;
	else
		max = RES_X;
	all->background.img = mlx_new_image(all->mlx.con, max * 4, max * 4);
	all->background.addr = mlx_get_data_addr(all->background.img,
	&all->background.bits_per_pixel, &all->background.line_length,
	&all->background.endian);

	all->flashlight.img = mlx_new_image(all->mlx.con, max * 4, max * 4);
	all->flashlight.addr = mlx_get_data_addr(all->flashlight.img,
	&all->flashlight.bits_per_pixel, &all->flashlight.line_length,
	&all->flashlight.endian);

	all->tmp_player.img = mlx_new_image(all->mlx.con, TEXTURE_SIZE,
	TEXTURE_SIZE);
	all->tmp_player.addr = mlx_get_data_addr(all->tmp_player.img,
	&all->tmp_player.bits_per_pixel, &all->tmp_player.line_length,
	&all->tmp_player.endian);
}

int	game(t_all *all)
{
	mlx_clear_window(all->mlx.con, all->mlx.window);
	mlx_put_image_to_window(all->mlx.con, all->mlx.window, all->sky.img, 0, 0);
	if (ALTERNATIVE_CONTROL == 1)
		check_movement(all);
	else
		check_movement2(all);
	mlx_put_image_to_window(all->mlx.con, all->mlx.window,
	all->background.img, 0 - (all->player.pos_x - RES_X / 2),
	0 - (all->player.pos_y - RES_Y / 2));
	// player_angle(all);
	// mlx_put_image_to_window(all->mlx.con, all->mlx.window,
	// all->flashlight.img, 0, 0);
	mlx_put_image_to_window(all->mlx.con, all->mlx.window,
	all->tmp_player.img, RES_X / 2, RES_Y / 2);
	return (1);
}


int x_cross_close(t_all *all)
{
	error_message("Good bye", all);
	exit (1);
	return (1);
}

void	fill_cos_table(t_all *all)
{
	int number;
	int end;
	int ugol;
	int counter;

	counter = 0;
	number = -1 * (RAYS / 2);
	end = RAYS / 2 + 1;
	ugol = all->player.rotate - (FIX_ANGLE * end);
	while (--end > number)
	{
		all->cos_table[counter] =
		cos(all->player.rotate - (FIX_ANGLE * end) - all->player.rotate);
		counter++;
	}
}

int main(int argc, char **argv)
{
	t_all all;

	if (argc != 2)
		error_message("Check arguments. Need only map with .ber extension", &all);
	all.mlx.con = mlx_init();
	if (!all.mlx.con)
		error_message("Fail initializing mlx", &all);
	all.mlx.window = mlx_new_window(all.mlx.con, RES_X, RES_Y, "so_long");
	if (!all.mlx.window)
		error_message("Fail opening window", &all);
	check_args(&all, argv[1]);
	fill_structure(&all);
	find_player(&all);
	make_flashlight(&all);
	fill_cos_table(&all);
	mlx_hook(all.mlx.window, 2, 1L << 0, &check_key, &all);
	mlx_key_hook(all.mlx.window, &key_release, &all);
	mlx_loop_hook(all.mlx.con, &game, &all);
	mlx_hook(all.mlx.window, 17, 1, x_cross_close, &all);
	mlx_loop(all.mlx.con);
	return (1);
}