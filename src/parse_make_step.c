/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_step.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:04:11 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:35:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		make_step(t_lemin *tl, t_ant **ant_arr, t_room *tv)
{
	t_room	*t;
	int			ant_id;

	ant_id = 0;
	t = tv;
	while (ant_id < tl->ant_num && ant_can_go(tl, ant_arr[ant_id], tv))
	{
		if ((ant_arr[ant_id]->room)->beg != -1)
		{
			make_step_thing(tl, ant_arr, tv, ant_id);
			output_ants(tl, ant_arr, ant_id);
			tv = t;
		}
		ant_id++;
	}
	ft_printf("\n");
}

int			beg_end_present(t_room *tv)
{
	t_room *tmp;

	tmp = tv;
	while (tv->next && tv->beg != 1)
		tv = tv->next;
	if (!tv->links[0])
		return (0);
	if (!(tv->next) && tv->beg != 1)
		return (0);
	tv = tmp;
	while (tv->next && tv->beg != -1)
		tv = tv->next;
	if (!tv->links[0])
		return (0);
	if (!(tv->next) && tv->beg != -1)
		return (0);
	tv = tmp;
	bfs(tv);
	while (tv->beg != -1)
		tv = tv->next;
	if (!(tv->dist))
		return (0);
	tv = tmp;
	return (1);
}

void		print_ways(t_room *tv, t_way *tw, t_lemin *tl)
{
	int			i;
	t_room	*tmp;

	tmp = tv;
	ft_printf("{GREEN}Paths:{RESET}\n");
	while (tw)
	{
		i = tw->dist;
		while (--i >= 0)
		{
			while (tw->way[i] != tv->id)
				tv = tv->next;
			if (i == tw->dist - 1)
				ft_printf("{ %s--->", tv->name);
			else if (i > 0)
				ft_printf("%s--->", tv->name);
			else
				ft_printf("%s }\n", tv->name);
			tv = tmp;
		}
		if (tl->show_ants)
			ft_printf("ants_num: %d\n", tw->ant_num);
		tw = tw->next;
	}
	ft_printf("\n");
}

int			beg_end_connected(t_room *tv)
{
	while (tv && tv->beg != -1)
		tv = tv->next;
	if (tv && tv->father && (tv->father)->beg == 1)
		return (1);
	return (0);
}

t_room	*parsing(t_lemin *tl)
{
	char			*line;
	t_room		*tv;
	int				i;

	tv = NULL;
	line = NULL;
	i = 0;
	while ((tl->gnl = get_next_line(tl->fd, &line)) > 0 && str_arr_remalloc(tl))
	{
		tl->print[tl->it++] = line;
		i++;
		if (antsnum_exception(line))
			continue ;
		if (!(antnum_cor(line)) || (!(tl->ant_num = ft_atoi(line))))
			ft_error(1);
		if (!(tv = read_rooms(line, tl)))
			ft_error(9);
		if (!(beg_end_present(tv)))
			ft_error(8);
		break ;
	}
	ft_strdel(&line);
	if (tl->gnl < 0 || !i)
		ft_error(2);
	return (tv);
}
