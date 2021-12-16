/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:57:05 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/10 17:30:45 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	rotate_player(t_all *all)
{
	if (all->player.press_rotate == -1)
		all->player.rotate -= (0.1 * ROTATION_SPEED / 10);
	if (all->player.press_rotate == 1)
		all->player.rotate += (0.1 * ROTATION_SPEED / 10);
	if (fabs(all->player.rotate) >= 2 * M_PI)
		all->player.rotate = 0;
}


int	check_key(int key, t_all *all)
{
	if (key == 49 && all->player.pres_jump == -1)
		all->player.pres_jump = 1;
	if (key == 257)
		all->player.movement_speed = MOVEMENT_SPEED * 2;
	if (key == 53)
		error_message("Game was closed via ESC button", all);
	if (key == 1)
		all->player.press_s = 1;
	if (key == 0)
		all->player.press_a = 1;
	if (key == 2)
		all->player.press_d = 1;
	if (key == 13)
		all->player.press_w = 1;
	if (key ==  123)
		all->player.press_rotate = -1;
	if (key ==  124)
		all->player.press_rotate = 1;
	return (1);
}

int	key_release(int key, t_all *all)
{
	if (key == 257)
		all->player.movement_speed = MOVEMENT_SPEED;
	if (key == 1)
		all->player.press_s = 0;
	if (key == 0)
		all->player.press_a = 0;
	if (key == 2)
		all->player.press_d = 0;
	if (key == 13)
		all->player.press_w = 0;
	if (key ==  123 || key == 124)
		all->player.press_rotate = 0;
	return (1);
}