/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:36:29 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 03:49:36 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		links_marked(t_room *tv)
{
	int i;

	i = 0;
	while (tv->links[i])
	{
		if (!tv->links[i]->marked && !tv->links[i]->used)
			return (0);
		i++;
	}
	return (1);
}

void	recalc_distance(t_room *tv)
{
	t_room	*tmp;
	int			i;

	while (tv)
	{
		tmp = tv;
		i = 0;
		while (tv)
		{
			tv = tv->father;
			i++;
		}
		tv = tmp;
		tv->distance = i;
		tv = tv->next;
	}
}

t_path	*find_path(t_room *tv)
{
	t_path		*tw;
	t_room	*tmp;
	int			i;

	i = 0;
	tw = (t_path *)malloc(sizeof(t_path));
	recalc_distance(tv);
	tmp = tv;
	while (tv && tv->beg != -1)
		tv = tv->next;
	tw->path = (int *)malloc(sizeof(int) * tv->distance);
	tw->distance = tv->distance;
	while (tv)
	{
		tw->path[i++] = tv->id;
		tv = tv->father;
		if (tv && tv->father)
			tv->used = 1;
	}
	tw->n_ants = 0;
	tw->next = NULL;
	tv = tmp;
	if (!(beg_end_connected(tv)))
		null_vertex(tv);
	return (tw);
}

int		realloc_darr(t_global *tl)
{
	static	int		iter = 1;
	char			**printcpy;
	int				i;

	if (iter == 1 || tl->map[BUFF] != NULL)
	{
		tl->n_lines = BUFF * iter;
		printcpy = ft_memalloc(sizeof(char *) * (tl->n_lines + 1));
		tl->n_lines -= BUFF;
		i = -1;
		while (++i < tl->n_lines)
			printcpy[i] = tl->map[i];
		i = -1;
		if (iter != 1)
			free(tl->map);
		else
			tl->iter = 0;
		tl->map = printcpy;
		iter++;
	}
	return (1);
}

bool		check_n_emm(char *line, int ind)
{
	if (ind == 1)
	{
		if (ft_strequ(line, "##start"))
			puterr("Error: ##start before number of ants");
		else if (ft_strequ(line, "##end"))
			puterr("Error: ##end before number of ants");
	}
	return (COMMENT(line) ? (false) : (true));
}
