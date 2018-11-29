/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_step.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:04:11 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 09:15:46 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		make_step(t_emmet **ant_arr, t_room *room)
{
	t_room	*t;
	int			ant_id;

	ant_id = 0;
	t = room;
	while (ant_id < gl->n_ants && ant_can_go(ant_arr[ant_id], room))
	{
		if ((ant_arr[ant_id]->room)->beg != -1)
		{
			make_step_thing(ant_arr, room, ant_id);
			output_emmets(ant_arr, ant_id);
			room = t;
		}
		ant_id++;
	}
	ft_printf("\n");
}

bool			stend_valid(t_room *room)
{
	t_room		*node;
	static bool	res = true;

	node = room;
	while (node->next && node->beg != 1)
		node = node->next;
	if (!node->links[0] || (!(node->next) && node->beg != 1))
		res = false;
	node = room;
	while (node->next && node->beg != -1)
		node = node->next;
	if (!node->links[0] || (!(node->next) && node->beg != -1))
		res = false;
	node = room;
	br_first_search(room);
	while (node->beg != -1)
		node = node->next;
	if (!(node->distance))
		res = false;
	return (res);
}

void		print_paths(t_room *room, t_path *path)
{
	int			i;
	t_room		*node;

	node = room;
	ft_printf("%sPossible ways:%s\n", GREEN, RESET);
	while (path && (i = path->distance))
	{
		while (--i >= 0)
		{
			while (path->path[i] != room->id)
				room = room->next;
			if (i == path->distance - 1)
				ft_printf("[ %s%s ==> ", g_col[path->n_path % 8], room->name);
			else if (i > 0)
				ft_printf("%s ==> ", room->name);
			else
				ft_printf("%s%s ]\n", room->name, RESET);
			room = node;
		}
		if (gl->disp_emmets)
			ft_printf("ants number on da way: %s%d%s\n",
			g_col[path->n_path % 8], path->n_ants, RESET);
		path = path->next;
	}
	ft_putchar('\n');
}

bool		st_end_nearby(t_room *room)
{
	bool	res;

	res = false;
	while (room && room->beg != -1)
		room = room->next;
	if (room && room->father && (room->father)->beg == 1)
		res = true;
	return (res);
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
		if (!check_n_emm(line))
			continue ;
		if (!(n_ants_valid(line)))
			puterr("Error: wrong number of ants");
		else
			break;
	}
	if (!(room = parse_val_rooms(line)))
		puterr("Error: wrong first room");
	if (!(stend_valid(room)))
		puterr("Error: wrong start/end, or there is no possible path");
	ft_strdel(&line);
	if (gl->gnl_ret < 0 || !ind)
		puterr("Error: invalid or empty file");
	return (room);
}
