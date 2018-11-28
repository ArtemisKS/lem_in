/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:00:56 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:35:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_ant_1(int ant_id, t_room *room,\
							int way_num, t_lemin *tl)
{
	char *room_name;

	room_name = room->name;
	if (!(way_num % 8) && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d-{MAGENTA}%s ", ant_id, room_name);
	else if (!(way_num % 8))
		ft_printf("{MAGENTA}L%d-%s ", ant_id, room_name);
	if ((way_num % 8 == 1) && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d{RESET}-%s ", ant_id, room_name);
	else if ((way_num % 8) == 1)
		ft_printf("{RESET}L%d-%s ", ant_id, room_name);
	if ((way_num % 8 == 2) && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d{BLUE}-%s ", ant_id, room_name);
	else if ((way_num % 8 == 2))
		ft_printf("{BLUE}L%d-%s ", ant_id, room_name);
	if ((way_num % 8 == 3) && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d{RED}-%s ", ant_id, room_name);
	else if ((way_num % 8) == 3)
		ft_printf("{RED}L%d-%s ", ant_id, room_name);
}

void			print_ant(int ant_id, t_room *room, int way_num, t_lemin *tl)
{
	char *room_name;

	room_name = room->name;
	print_ant_1(ant_id, room, way_num, tl);
	if ((way_num % 8 == 4) && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d{YELLOW}-%s ", ant_id, room_name);
	else if ((way_num % 8) == 4)
		ft_printf("{YELLOW}L%d-%s ", ant_id, room_name);
	if ((way_num % 8 == 5) && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d{LRED}-%s ", ant_id, room_name);
	else if ((way_num % 8) == 5)
		ft_printf("{LRED}L%d-%s ", ant_id, room_name);
	if ((way_num % 8) == 6 && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d{BROWN}-%s ", ant_id, room_name);
	else if ((way_num % 8) == 6)
		ft_printf("{BROWN}L%d-%s ", ant_id, room_name);
	if ((way_num % 8 == 7) && tl->ants_home && room->beg == -1)
		ft_printf("{GREEN}L%d{CYAN}-%s ", ant_id, room_name);
	else if ((way_num % 8) == 7)
		ft_printf("{CYAN}L%d-%s ", ant_id, room_name);
}

static void		free_vert(t_room *tv)
{
	ft_strdel(&tv->name);
	if (tv->father)
		ft_memdel((void **)&tv->father);
	ft_memdel((void **)&tv);
}

void			make_step_thing(t_lemin *tl, t_ant **ant_arr,\
								t_room *tv, int ant_id)
{
	t_room *t;

	t = tv;
	(ant_arr[ant_id]->room)->occupied = 0;
	while ((ant_arr[ant_id]->room)->id != tv->id)
		tv = tv->next;
	tv->occupied = 0;
	tv = t;
	free_vert(ant_arr[ant_id]->room);
	ant_arr[ant_id]->room = (ant_arr[ant_id]->room)->next;
	(ant_arr[ant_id]->room)->occupied = 1;
	while ((ant_arr[ant_id]->room)->id != tv->id)
		tv = tv->next;
	if (tv->beg == -1)
		tl->gone_ants++;
	else
		tv->occupied = 1;
}

void			output_ants(t_lemin *tl, t_ant **ant_arr, int ant_id)
{
	if (tl->col)
		print_ant(ant_id + 1, ant_arr[ant_id]->room,
			(ant_arr[ant_id]->way)->way_num, tl);
	else if (tl->ants_home)
	{
		if ((ant_arr[ant_id]->room)->beg == -1)
			ft_printf("{GREEN}L%d{RESET}-%s ",
				ant_id + 1, (ant_arr[ant_id]->room)->name);
		else
			ft_printf("L%d-%s ", ant_id + 1,
				(ant_arr[ant_id]->room)->name);
	}
	else
		ft_printf("L%d-%s ", ant_id + 1,
			(ant_arr[ant_id]->room)->name);
}
