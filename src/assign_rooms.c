/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 08:59:01 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 09:07:18 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		assign_rooms(t_emmet **ant_arr, t_room *tv)
{
	int i;

	i = 0;
	while (i < gl->n_ants)
	{
		ant_arr[i]->room = make_rooms(ant_arr[i]->path, tv);
		i++;
	}
}

int			ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int			ant_can_go(t_emmet *ant, t_room *tv)
{
	int i;

	i = 0;
	while ((ant->room)->next && ((ant->room)->next)->id != tv->id)
		tv = tv->next;
	if ((ant->room)->beg == -1 && ant->id < gl->n_ants)
		return (1);
	if ((!(ant->room)->next && (ant->room)->beg == -1
		&& ant->id == gl->n_ants) || tv->occupied)
		return (0);
	return (1);
}

bool			n_ants_valid(char *line)
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

void		bzero_room(t_room *tv)
{
	while (tv)
	{
		tv->distance = 0;
		tv->marked = 0;
		tv->father = NULL;
		tv = tv->next;
	}
}
