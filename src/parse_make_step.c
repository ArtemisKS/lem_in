/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_step.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:04:11 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 00:21:17 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		make_step(t_global *tl, t_emmet **ant_arr, t_room *tv)
{
	t_room	*t;
	int			ant_id;

	ant_id = 0;
	t = tv;
	while (ant_id < tl->n_ants && ant_can_go(tl, ant_arr[ant_id], tv))
	{
		if ((ant_arr[ant_id]->room)->beg != -1)
		{
			make_step_thing(tl, ant_arr, tv, ant_id);
			output_emmets(tl, ant_arr, ant_id);
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
	if (!(tv->distance))
		return (0);
	tv = tmp;
	return (1);
}

void		print_paths(t_room *tv, t_path *tw, t_global *tl)
{
	int			i;
	t_room	*tmp;

	tmp = tv;
	ft_printf("{GREEN}Paths:{RESET}\n");
	while (tw)
	{
		i = tw->distance;
		while (--i >= 0)
		{
			while (tw->path[i] != tv->id)
				tv = tv->next;
			if (i == tw->distance - 1)
				ft_printf("{ %s--->", tv->name);
			else if (i > 0)
				ft_printf("%s--->", tv->name);
			else
				ft_printf("%s }\n", tv->name);
			tv = tmp;
		}
		if (tl->disp_emmets)
			ft_printf("ants_num: %d\n", tw->n_ants);
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

t_room	*parsing(t_global *tl)
{
	char			*line;
	t_room		*tv;
	int				i;

	tv = NULL;
	line = NULL;
	i = 0;
	while ((tl->gnl_ret = get_next_line(tl->fd, &line)) > 0 && str_arr_remalloc(tl))
	{
		tl->map[tl->it++] = line;
		i++;
		if (antsnum_exception(line))
			continue ;
		if (!(antnum_cor(line)) || (!(tl->n_ants = ft_atoi(line))))
			ft_error(1);
		if (!(tv = read_rooms(line, tl)))
			ft_error(9);
		if (!(beg_end_present(tv)))
			ft_error(8);
		break ;
	}
	ft_strdel(&line);
	if (tl->gnl_ret < 0 || !i)
		ft_error(2);
	return (tv);
}
