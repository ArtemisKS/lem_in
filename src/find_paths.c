/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:36:29 by akupriia          #+#    #+#             */
/*   Updated: 2018/05/08 18:36:30 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		kids_visited(t_vertex *tv)
{
	int i;

	i = 0;
	while (tv->kids[i])
	{
		if (!tv->kids[i]->visited && !tv->kids[i]->taken)
			return (0);
		i++;
	}
	return (1);
}

void	recalc_dist(t_vertex *tv)
{
	t_vertex	*tmp;
	int			i;

	while (tv)
	{
		tmp = tv;
		i = 0;
		while (tv)
		{
			tv = tv->parent;
			i++;
		}
		tv = tmp;
		tv->dist = i;
		tv = tv->next;
	}
}

t_way	*find_path(t_vertex *tv)
{
	t_way		*tw;
	t_vertex	*tmp;
	int			i;

	i = 0;
	tw = (t_way *)malloc(sizeof(t_way));
	recalc_dist(tv);
	tmp = tv;
	while (tv && tv->start != -1)
		tv = tv->next;
	tw->way = (int *)malloc(sizeof(int) * tv->dist);
	tw->dist = tv->dist;
	while (tv)
	{
		tw->way[i++] = tv->id;
		tv = tv->parent;
		if (tv && tv->parent)
			tv->taken = 1;
	}
	tw->ant_num = 0;
	tw->next = NULL;
	tv = tmp;
	if (!(start_end_connected(tv)))
		null_vertex(tv);
	return (tw);
}

int		str_arr_remalloc(t_lemin *tl)
{
	static	int		iter = 1;
	char			**printcpy;
	int				i;

	if (iter == 1 || tl->print[BUFF] != NULL)
	{
		tl->sum = BUFF * iter;
		printcpy = ft_memalloc(sizeof(char *) * (tl->sum + 1));
		tl->sum -= BUFF;
		i = -1;
		while (++i < tl->sum)
			printcpy[i] = tl->print[i];
		i = -1;
		if (iter != 1)
			free(tl->print);
		else
			tl->it = 0;
		tl->print = printcpy;
		iter++;
	}
	return (1);
}

int		antsnum_exception(char *line)
{
	if (!ft_strcmp(line, "##start"))
		ft_error(3);
	if (!ft_strcmp(line, "##end"))
		ft_error(3);
	if (line && line[0] == '#')
		return (1);
	if (line && !(ft_strlen(line)))
		ft_error(3);
	return (0);
}
