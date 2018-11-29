/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:00:56 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 08:31:44 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_emmet(int ant_id, t_room *room, int n_path)
{
	char		*room_n;

	room_n = room->name;
	ft_printf("%sL%d-%s%s ", g_col[n_path % 8], ant_id, (gl->ants_home && room->beg == -1)
		? GREEN : "", room_n);
}

static void		free_vert(t_room *tv)
{
	ft_strdel(&tv->name);
	if (tv->father)
		ft_memdel((void **)&tv->father);
	ft_memdel((void **)&tv);
}

void			make_step_thing(t_emmet **arr_em_str,
		t_room *tv, int ant_id)
{
	t_room *t;

	t = tv;
	(arr_em_str[ant_id]->room)->occupied = 0;
	while ((arr_em_str[ant_id]->room)->id != tv->id)
		tv = tv->next;
	tv->occupied = 0;
	tv = t;
	free_vert(arr_em_str[ant_id]->room);
	arr_em_str[ant_id]->room = (arr_em_str[ant_id]->room)->next;
	(arr_em_str[ant_id]->room)->occupied = 1;
	while ((arr_em_str[ant_id]->room)->id != tv->id)
		tv = tv->next;
	if (tv->beg == -1)
		gl->n_ants_arr++;
	else
		tv->occupied = 1;
}

void			output_emmets(t_emmet **arr_em_str, int ant_id)
{
	if (gl->colour)
		print_emmet(ant_id + 1, arr_em_str[ant_id]->room,
			(arr_em_str[ant_id]->path)->n_path);
	else if (gl->ants_home)
	{
		if ((arr_em_str[ant_id]->room)->beg == -1)
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
