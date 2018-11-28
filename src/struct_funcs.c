/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:50:08 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:35:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lemin		*make_lemin(void)
{
	t_lemin *tl;

	tl = (t_lemin *)malloc(sizeof(t_lemin));
	tl->fd = 0;
	tl->ant_num = 0;
	tl->way_num = 0;
	tl->gone_ants = 0;
	tl->col = 0;
	tl->show_ways = 0;
	tl->show_ants = 0;
	tl->leaks = 0;
	tl->ants_home = 0;
	tl->sum = 0;
	tl->gnl = 0;
	return (tl);
}

t_room	*make_struct(void)
{
	t_room *tv;

	tv = (t_room *)malloc(sizeof(t_room));
	tv->links = (t_room **)malloc(sizeof(t_room *) * 100);
	tv->father = NULL;
	tv->next = NULL;
	tv->name = NULL;
	tv->marked = 0;
	tv->occupied = 0;
	tv->used = 0;
	tv->x = 0;
	tv->y = 0;
	tv->dist = 0;
	tv->n_links = 0;
	tv->id = 0;
	tv->beg = 0;
	return (tv);
}

t_room	*copy_kid(t_room *tv)
{
	t_room	*res;
	int			j;

	j = 0;
	res = (t_room *)malloc(sizeof(t_room));
	res->links = NULL;
	res->father = NULL;
	res->marked = tv->marked;
	res->occupied = tv->occupied;
	res->x = tv->x;
	res->y = tv->y;
	res->dist = tv->dist;
	res->n_links = tv->n_links;
	res->id = tv->id;
	res->beg = tv->beg;
	res->next = NULL;
	res->name = ft_strdup(tv->name);
	return (res);
}

void		ft_error(int n)
{
	if (n == 1)
		ft_putendl_fd("ANTS NUM ERROR", 2);
	else if (n == 3)
		ft_putendl_fd("beg OR END BEFORE ANTS ERROR", 2);
	else if (n == 4)
		ft_putendl_fd("WRONG ROOM OR FIRST LINK ERROR", 2);
	else if (n == 5)
		ft_putendl_fd("WRONG LINK ERROR", 2);
	else if (n == 6)
		ft_putendl_fd("WRONG ROOM ERROR", 2);
	else if (n == 7)
		ft_putendl_fd("beg OR END ERROR", 2);
	else if (n == 8)
		ft_putendl_fd("NO beg OR END OR NO POSSIBLE WAY ERROR", 2);
	else if (n == 9)
		ft_putendl_fd("WRONG FIRST ROOM ERROR", 2);
	else if (n == 2)
		ft_putendl_fd("STDIN ERROR", 2);
	else
		ft_putendl_fd("ERROR", 2);
	exit(1);
}

void		free_arr(void **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
