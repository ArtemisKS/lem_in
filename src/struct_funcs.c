/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:50:08 by akupriia          #+#    #+#             */
/*   Updated: 2018/06/03 19:50:09 by akupriia         ###   ########.fr       */
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

t_vertex	*make_struct(void)
{
	t_vertex *tv;

	tv = (t_vertex *)malloc(sizeof(t_vertex));
	tv->kids = (t_vertex **)malloc(sizeof(t_vertex *) * 100);
	tv->parent = NULL;
	tv->next = NULL;
	tv->name = NULL;
	tv->visited = 0;
	tv->busy = 0;
	tv->taken = 0;
	tv->x = 0;
	tv->y = 0;
	tv->dist = 0;
	tv->kids_num = 0;
	tv->id = 0;
	tv->start = 0;
	return (tv);
}

t_vertex	*copy_kid(t_vertex *tv)
{
	t_vertex	*res;
	int			j;

	j = 0;
	res = (t_vertex *)malloc(sizeof(t_vertex));
	res->kids = NULL;
	res->parent = NULL;
	res->visited = tv->visited;
	res->busy = tv->busy;
	res->x = tv->x;
	res->y = tv->y;
	res->dist = tv->dist;
	res->kids_num = tv->kids_num;
	res->id = tv->id;
	res->start = tv->start;
	res->next = NULL;
	res->name = ft_strdup(tv->name);
	return (res);
}

void		ft_error(int n)
{
	if (n == 1)
		ft_putendl_fd("ANTS NUM ERROR", 2);
	else if (n == 3)
		ft_putendl_fd("START OR END BEFORE ANTS ERROR", 2);
	else if (n == 4)
		ft_putendl_fd("WRONG ROOM OR FIRST LINK ERROR", 2);
	else if (n == 5)
		ft_putendl_fd("WRONG LINK ERROR", 2);
	else if (n == 6)
		ft_putendl_fd("WRONG ROOM ERROR", 2);
	else if (n == 7)
		ft_putendl_fd("START OR END ERROR", 2);
	else if (n == 8)
		ft_putendl_fd("NO START OR END OR NO POSSIBLE WAY ERROR", 2);
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
