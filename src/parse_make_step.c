/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_step.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:04:11 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 04:37:04 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		make_step(t_global *gl, t_emmet **ant_arr, t_room *room)
{
	t_room	*t;
	int			ant_id;

	ant_id = 0;
	t = room;
	while (ant_id < gl->n_ants && ant_can_go(gl, ant_arr[ant_id], room))
	{
		if ((ant_arr[ant_id]->room)->beg != -1)
		{
			make_step_thing(gl, ant_arr, room, ant_id);
			output_emmets(gl, ant_arr, ant_id);
			room = t;
		}
		ant_id++;
	}
	ft_printf("\n");
}

int			beg_end_present(t_room *room)
{
	t_room *tmp;

	tmp = room;
	while (room->next && room->beg != 1)
		room = room->next;
	if (!room->links[0])
		return (0);
	if (!(room->next) && room->beg != 1)
		return (0);
	room = tmp;
	while (room->next && room->beg != -1)
		room = room->next;
	if (!room->links[0])
		return (0);
	if (!(room->next) && room->beg != -1)
		return (0);
	room = tmp;
	bfs(room);
	while (room->beg != -1)
		room = room->next;
	if (!(room->distance))
		return (0);
	room = tmp;
	return (1);
}

void		print_paths(t_room *room, t_path *tw, t_global *gl)
{
	int			i;
	t_room		*tmp;

	tmp = room;
	ft_printf("{GREEN}Paths:{RESET}\n");
	while (tw)
	{
		i = tw->distance;
		while (--i >= 0)
		{
			while (tw->path[i] != room->id)
				room = room->next;
			if (i == tw->distance - 1)
				ft_printf("{ %s--->", room->name);
			else if (i > 0)
				ft_printf("%s--->", room->name);
			else
				ft_printf("%s }\n", room->name);
			room = tmp;
		}
		if (gl->disp_emmets)
			ft_printf("ants_num: %d\n", tw->n_ants);
		tw = tw->next;
	}
	ft_printf("\n");
}

int			beg_end_connected(t_room *room)
{
	while (room && room->beg != -1)
		room = room->next;
	if (room && room->father && (room->father)->beg == 1)
		return (1);
	return (0);
}

t_room		*parse_validate(t_global *gl)
{
	char			*line;
	t_room			*room;
	int				ind;

	room = NULL;
	ind = 0;
	while ((gl->gnl_ret = get_next_line(gl->fd, &line)) > 0
		&& realloc_darr(gl) && ++ind && (gl->map[gl->iter++] = line))
	{
		if (!check_n_emm(line, ind))
			continue ;
		if (ind == 1 && !(n_ants_valid(line, gl)))
			puterr("Error: wrong number of ants");
		if (!(room = read_rooms(line, gl)))
			puterr("Error: wrong first room");
		if (!(beg_end_present(room)))
			puterr("Error: wrong start/end, or there is no possible path");
		break ;
	}
	ft_strdel(&line);
	if (gl->gnl_ret < 0 || !ind)
		puterr("Error: invalid or empty file");
	return (room);
}
