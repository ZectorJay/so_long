/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:32:43 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/16 18:47:55 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	w_move2(t_all *all)
{
	// all->player.old_pos_x = all->player.pos_x;
	// all->player.old_pos_y = all->player.pos_y;
	// all->player.pos_y -= (1 * all->player.movement_speed / 10);
	// if (all->map[YSTOP][XSTOP] == '1')
	// {
	// 	all->player.pos_x = all->player.old_pos_x;
	// 	all->player.pos_y = all->player.old_pos_y;
	// }
}

void	s_move2(t_all *all)
{
	// all->player.old_pos_x = all->player.pos_x;
	// all->player.old_pos_y = all->player.pos_y;
	// all->player.pos_y += (1 * all->player.movement_speed / 10);
	// if (all->map[YSTOP][XSTOP] == '1')
	// {
	// 	all->player.pos_x = all->player.old_pos_x;
	// 	all->player.pos_y = all->player.old_pos_y;
	// }
}

void	a_move2(t_all *all)
{
	all->player.old_pos_x =
	all->player.pos_x - (1 * all->player.movement_speed / 10);
	all->player.old_pos_y = all->player.pos_y;
	// if (all->map[Y_STOP][X_STOP] != '1')
		all->player.pos_x -= (1 * all->player.movement_speed / 10);
}

void	d_move2(t_all *all)
{
	all->player.old_pos_x =
	all->player.pos_x + (1 * all->player.movement_speed / 10);
	all->player.old_pos_y = all->player.pos_y;
	// printf("x%f\n", all->player.old_pos_x / TEXTURE_SIZE);
	// printf("y%f\n", all->player.old_pos_y / TEXTURE_SIZE);
	// printf("Y - %d X - %d MAP[Y][X] = %c\n",
	// Y_STOP, X_STOP + 1, all->map[Y_STOP][X_STOP + 1]);
	// if (all->map[Y_STOP][X_STOP + 1] != '1')
		all->player.pos_x += (1 * all->player.movement_speed / 10);
	// if (all->map[YSTOP][XSTOP] != '1' && all->jump_flag != -1)
	// {
	// 	while (all->map[YSTOP - 1][XSTOP] != '1')
	// 		all->player.pos_y++;
	// }
}

void	*jump_func(void *new)
{
	t_all *all = (t_all *)new;
	int i;
	int j;

	j = 2000;
	i = 0;
	while (i++ < (TEXTURE_SIZE + TEXTURE_SIZE / 4))
	{
		all->player.pos_y -= 1;
		usleep(j += 50);
		if (j > 5000)
			j = 4950;
	}
	while (all->map[YSTOP + 1][XSTOP] != '1')
	{
	// printf("x%f\n", all->player.pos_x / TEXTURE_SIZE);
	// printf("y%f\n", all->player.pos_y / TEXTURE_SIZE);
	// printf("Y - %d X - %d MAP[Y][X] = %c\n",
	// YSTOP, XSTOP + 1, all->map[YSTOP][XSTOP + 1]);
		all->player.pos_y += 1;
		usleep(j -= 50);
		if (j == 1500)
			j = 1550;
	}
	all->player.pres_jump = -1;
	return (NULL);
}

void	check_movement2(t_all *all)
{
	if (all->player.pres_jump == 1)
	{
		all->player.pres_jump = 2;
		pthread_create(&all->thread, NULL, jump_func, all);
	}
	if (all->player.press_s == 1)
		s_move2(all);
	if (all->player.press_a == 1)
		a_move2(all);
	if (all->player.press_d == 1)
		d_move2(all);
	if (all->player.press_w == 1)
		w_move2(all);
	if (all->player.press_rotate)
		rotate_player(all);
}