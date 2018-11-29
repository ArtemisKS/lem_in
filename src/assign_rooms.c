/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:57:58 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 04:34:35 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		assign_rooms(t_global *tl, t_emmet **ant_arr, t_room *tv)
{
	int i;

	i = 0;
	while (i < tl->n_ants)
	{
		ant_arr[i]->room = make_rooms(ant_arr[i]->path, tv);
		i++;
	}
}

int			ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int			ant_can_go(t_global *tl, t_emmet *ant, t_room *tv)
{
	int i;

	i = 0;
	while ((ant->room)->next && ((ant->room)->next)->id != tv->id)
		tv = tv->next;
	if ((ant->room)->beg == -1 && ant->id < tl->n_ants)
		return (1);
	if ((!(ant->room)->next && (ant->room)->beg == -1
		&& ant->id == tl->n_ants) || tv->occupied)
		return (0);
	return (1);
}

bool			n_ants_valid(char *line, t_global *gl)
{
	int i;

	i = -1;
	if (!(is_int(line)) || line[0] == '0')
		return (false);
	while (line[++i])
		if (!(ft_isdigit(line[i])))
			return (false);
	gl->n_ants = ft_atoi(line);
	return (true);
}

void		null_vertex(t_room *tv)
{
	while (tv)
	{
		tv->father = NULL;
		tv->marked = 0;
		tv->distance = 0;
		tv = tv->next;
	}
}
