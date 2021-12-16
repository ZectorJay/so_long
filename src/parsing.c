/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:41:39 by hmickey           #+#    #+#             */
/*   Updated: 2021/12/10 18:59:04 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_all *all)
{
	int i;

	i = -1;
	while (all->map[++i])
	{
		write(1, all->map[i], ft_strlen(all->map[i]));
		write(1, "\n", 1);
	}
}

void	error_message(char *message, t_all *all)
{
	(void)all;
	write(1, RED, 6);
	ft_putstr_fd(message, 1);
	write(1, RESET, 5);
	exit(1);
}

void	fill_img(t_all *all, t_texture *target, char *name)
{
	target->img = mlx_xpm_file_to_image(all->mlx.con, name, &target->width, &target->height);
	if (!target->img)
		error_message("fail to open .xpm image for textures", all);
	target->addr = mlx_get_data_addr(target->img, &target->bits_per_pixel,
		&target->line_length, &target->endian);
	if (!target->addr)
		error_message("fail during getting .xpm data", all);
}

void	count_lines(t_all *all, int fd)
{
	char	*line;
	int		reading;

	reading = 1;
	while (reading)
	{
		reading = get_next_line(fd, &line);
		free(line);
		if (reading < 0)
			error_message("Error during reading file", all);
		all->counter++;
	}
}

void	read_map(t_all *all, char *file_name)
{
	int fd;
	int reading;

	reading = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_message("fail opening map", all);
	all->counter = 1;
	count_lines(all, fd);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_message("fail opening map", all);
	all->map = (char**)malloc(sizeof(char *) * (all->counter));
	all->counter = 0;
	while (reading)
	{
		reading = get_next_line(fd, &all->map[all->counter++]);
		if (reading < 0)
			error_message("Error during reading file", all);
	}
	all->map[all->counter] = NULL;
}

void	check_args(t_all *all, char *file_name)
{
	fill_img(all, &all->walls, "./img/bricks.xpm");
	get_color(&all->walls);
	fill_img(all, &all->floor, "./img/555.xpm");
	get_color(&all->floor);
	fill_img(all, &all->collect, "img/collect2.xpm");
	get_color(&all->collect);
	fill_img(all, &all->exit, "./img/exit.xpm");
	get_color(&all->exit);
	fill_img(all, &all->character, "./img/chr.xpm");
	get_color(&all->character);
	fill_img(all, &all->sky, "./img/sky.xpm");
	read_map(all, file_name);
}