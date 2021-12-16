/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:17:49 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/09 15:34:28 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	w_move(t_all *all)
{
	all->player.old_pos_x = all->player.pos_x;
	all->player.old_pos_y = all->player.pos_y;
	all->player.pos_x -= cos(all->player.rotate) * (all->player.movement_speed / 10);
	all->player.pos_y -= sin(all->player.rotate) * (all->player.movement_speed / 10);
	if (all->map[YSTOP][XSTOP] == '1')
	{
		all->player.pos_x = all->player.old_pos_x;
		all->player.pos_y = all->player.old_pos_y;
	}
}

void	s_move(t_all *all)
{
	all->player.old_pos_x = all->player.pos_x;
	all->player.old_pos_y = all->player.pos_y;
	all->player.pos_x += cos(all->player.rotate) * (all->player.movement_speed / 10);
	all->player.pos_y += sin(all->player.rotate) * (all->player.movement_speed / 10);
	if (all->map[YSTOP][XSTOP] == '1')
	{
		all->player.pos_x = all->player.old_pos_x;
		all->player.pos_y = all->player.old_pos_y;
	}
}

void	a_move(t_all *all)
{
	all->player.old_pos_x = all->player.pos_x;
	all->player.old_pos_y = all->player.pos_y;
	all->player.pos_y += cos(all->player.rotate) * (all->player.movement_speed / 10);
	all->player.pos_x -= sin(all->player.rotate) * (all->player.movement_speed / 10);
	if (all->map[YSTOP][XSTOP] == '1')
	{
		all->player.pos_x = all->player.old_pos_x;
		all->player.pos_y = all->player.old_pos_y;
	}
}

void	d_move(t_all *all)
{
	all->player.old_pos_x = all->player.pos_x;
	all->player.old_pos_y = all->player.pos_y;
	all->player.pos_y -= cos(all->player.rotate) * (all->player.movement_speed / 10);
	all->player.pos_x += sin(all->player.rotate) * (all->player.movement_speed / 10);
	if (all->map[YSTOP][XSTOP] == '1')
	{
		all->player.pos_x = all->player.old_pos_x;
		all->player.pos_y = all->player.old_pos_y;
	}
}

void	check_movement(t_all *all)
{
	if (all->player.press_s == 1)
		s_move(all);
	if (all->player.press_a == 1)
		a_move(all);
	if (all->player.press_d == 1)
		d_move(all);
	if (all->player.press_w == 1)
		w_move(all);
	if (all->player.press_rotate)
		rotate_player(all);
}