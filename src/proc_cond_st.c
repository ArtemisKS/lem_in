/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_cond_st.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:25:54 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 04:48:49 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void			cond_one_st(t_emmet **ant_arr, t_room *room)
{
	t_room		*node;
	int			ant_id;

	ant_id = -1;
	node = room;
	while (++ant_id < g_gl->n_ants && emm_may_move(ant_arr[ant_id], room))
		if ((ant_arr[ant_id]->room)->status != 'e')
		{
			cond_one_st_thing(ant_arr, room, ant_id);
			do_emm_printing(ant_arr, ant_id);
			room = node;
		}
	ft_putchar('\n');
}

bool			stend_valid(t_room *room)
{
	t_room		*node;

	node = room;
	while (node->next && node->status != 's')
		node = node->next;
	if (!node->links[0] || (!(node->next) && node->status != 's'))
		return (false);
	node = room;
	while (node->next && node->status != 'e')
		node = node->next;
	if (!node->links[0] || (!(node->next) && node->status != 'e'))
		return (false);
	node = room;
	br_first_search(room);
	while (node->status != 'e')
		node = node->next;
	if (!(node->distance))
		return (false);
	return (true);
}

void			print_paths(t_room *room, t_path *path)
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
		if (g_gl->disp_emmets)
			ft_printf("ants number on da way: %s%d%s\n",
			g_col[path->n_path % 8], path->n_ants, RESET);
		path = path->next;
	}
	ft_putchar('\n');
}

bool			st_end_nearby(t_room *room)
{
	bool	res;

	res = false;
	while (room && room->status != 'e')
		room = room->next;
	if (room && room->father && (room->father)->status == 's')
		res = true;
	return (res);
}

t_room			*parse_validate(void)
{
	char			*str;
	t_room			*room;
	int				ind;

	room = NULL;
	ind = 0;
	while ((g_gl->gnl_ret = get_next_line(g_gl->fd, &str)) > 0
	&& realloc_darr() && ++ind && (g_gl->map[g_gl->iter++] = str))
	{
		if (!check_n_emm(str))
			continue ;
		if (!(n_ants_valid(str)))
			puterr("Error: wrong number of ants");
		else
			break ;
	}
	if (!(room = parse_val_rooms(str)))
		puterr("Error: wrong first room");
	if (!(stend_valid(room)))
		puterr("Error: wrong start/end, or there is no possible path");
	ft_strdel(&str);
	if (g_gl->gnl_ret < 0 || !ind)
		puterr("Error: invalid or empty file");
	(g_gl->fd) ? close(g_gl->fd) : 1;
	return (room);
}
