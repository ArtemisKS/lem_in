/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:00:56 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 15:37:33 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					print_emmet(int ant_id, t_room *room, int n_path)
{
	char		*room_n;

	room_n = room->name;
	ft_printf("%sL%d-%s%s ", g_col[n_path % 8], ant_id, (gl->ants_home && room->beg == 'e')
		? GREEN : "", room_n);
}

static inline void		mdel_room(t_room *room)
{
	ft_strdel(&room->name);
	if (room->father)
		ft_memdel((void **)&room->father);
	ft_memdel((void **)&room);
}

void					cond_one_st_thing(t_emmet **arr_em_str,
		t_room *room, int ant_id)
{
	t_room *t;

	t = room;
	(arr_em_str[ant_id]->room)->occupied = 0;
	while ((arr_em_str[ant_id]->room)->id != room->id)
		room = room->next;
	room->occupied = 0;
	room = t;
	mdel_room(arr_em_str[ant_id]->room);
	arr_em_str[ant_id]->room = (arr_em_str[ant_id]->room)->next;
	(arr_em_str[ant_id]->room)->occupied = 1;
	while ((arr_em_str[ant_id]->room)->id != room->id)
		room = room->next;
	if (room->beg == 'e')
		gl->n_ants_arr++;
	else
		room->occupied = 1;
}

void					output_emmets(t_emmet **arr_em_str, int ant_id)
{
	if (gl->colour)
		print_emmet(ant_id + 1, arr_em_str[ant_id]->room,
			(arr_em_str[ant_id]->path)->n_path);
	else if (gl->ants_home)
	{
		if ((arr_em_str[ant_id]->room)->beg == 'e')
			ft_printf("L%d-%s%s%s ", ant_id + 1,
			GREEN, (arr_em_str[ant_id]->room)->name, RESET);
		else
			ft_printf("L%d-%s ", ant_id + 1,
				(arr_em_str[ant_id]->room)->name);
	}
	else
		ft_printf("L%d-%s ", ant_id + 1,
			(arr_em_str[ant_id]->room)->name);
}
