/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cout_emmets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:25:04 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 04:24:49 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void					print_emmet(int ant_id, t_room *room, int n_path)
{
	char		*room_n;

	room_n = room->name;
	ft_printf("%sL%d-%s%s ", g_col[n_path % 8], ant_id,
	(g_gl->ants_home && room->status == 'e')
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
	(room->status == 'e') ? (g_gl->n_ants_arr++) : (room->occupied = 1);
}

void					do_emm_printing(t_emmet **arr_em_str, int ant_id)
{
	if (g_gl->colour)
		print_emmet(ant_id + 1, arr_em_str[ant_id]->room,
			(arr_em_str[ant_id]->path)->n_path);
	else if (g_gl->ants_home)
	{
		if ((arr_em_str[ant_id]->room)->status == 'e')
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
