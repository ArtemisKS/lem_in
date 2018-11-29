/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_cond_st.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:38:58 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 15:42:53 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		cond_one_st(t_emmet **ant_arr, t_room *room)
{
	t_room	*t;
	int			ant_id;

	ant_id = 0;
	t = room;
	while (ant_id < gl->n_ants && emm_may_move(ant_arr[ant_id], room))
	{
		if ((ant_arr[ant_id]->room)->beg != 'e')
		{
			cond_one_st_thing(ant_arr, room, ant_id);
			output_emmets(ant_arr, ant_id);
			room = t;
		}
		ant_id++;
	}
	ft_putchar('\n');
}

bool			stend_valid(t_room *room)
{
	t_room		*node;
	static bool	res = true;

	node = room;
	while (node->next && node->beg != 's')
		node = node->next;
	if (!node->links[0] || (!(node->next) && node->beg != 's'))
		res = false;
	node = room;
	while (node->next && node->beg != 'e')
		node = node->next;
	if (!node->links[0] || (!(node->next) && node->beg != 'e'))
		res = false;
	node = room;
	br_first_search(room);
	while (node->beg != 'e')
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
	while (room && room->beg != 'e')
		room = room->next;
	if (room && room->father && (room->father)->beg == 's')
		res = true;
	return (res);
}

t_room		*parse_validate(void)
{
	char			*str;
	t_room			*room;
	int				ind;

	room = NULL;
	ind = 0;
	while ((gl->gnl_ret = get_next_line(gl->fd, &str)) > 0 && realloc_darr() && ++ind && (gl->map[gl->iter++] = str))
	{
		if (!check_n_emm(str))
			continue ;
		if (!(n_ants_valid(str)))
			puterr("Error: wrong number of ants");
		else
			break;
	}
	if (!(room = parse_val_rooms(str)))
		puterr("Error: wrong first room");
	if (!(stend_valid(room)))
		puterr("Error: wrong start/end, or there is no possible path");
	ft_strdel(&str);
	if (gl->gnl_ret < 0 || !ind)
		puterr("Error: invalid or empty file");
	(gl->fd) ? close(gl->fd) : 1;
	return (room);
}
