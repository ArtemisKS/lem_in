/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 21:14:50 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:35:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			int_value(char *line)
{
	int		i;
	char	*s;

	i = -1;
	s = "2147483647\0";
	while (line[++i])
		;
	if (i > 10)
		return (0);
	else if (i == 10)
	{
		i = -1;
		while (line[++i])
		{
			if (line[i] > s[i])
				return (0);
			else if (line[i] < s[i])
				return (1);
		}
	}
	return (1);
}

t_way		*alg_and_sth_else(t_room *tv)
{
	int		i;
	t_way	*tmp;
	t_way	*tw;

	i = 0;
	tmp = NULL;
	tw = NULL;
	while (!i || linked_with_end(tv))
	{
		tmp = find_path(tv);
		tmp->way_num = i + 1;
		if (!i)
			tw = tmp;
		else
			ft_wpush(&tw, tmp);
		if (!i && beg_end_connected(tv))
			break ;
		tmp = tmp->next;
		i++;
	}
	while (tv->beg != 1)
		tv = tv->next;
	tv->occupied = 1;
	return (tw);
}

t_ant		**ants_init(t_lemin *tl, t_way *tw)
{
	int		i;
	t_way	*tmp;
	t_ant	**ant_arr;

	i = 0;
	ant_arr = (t_ant **)malloc(sizeof(t_ant *) * tl->ant_num);
	while (i < tl->ant_num)
	{
		ant_arr[i] = (t_ant *)malloc(sizeof(t_ant));
		ant_arr[i]->room = NULL;
		ant_arr[i]->id = i + 1;
		i++;
	}
	tmp = tw;
	i = 0;
	while (tw)
	{
		i++;
		tw->occupied = 0;
		tw = tw->next;
	}
	tw = tmp;
	return (ant_arr);
}

void		do_flags(int ac, char **av, t_lemin *tl)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!(ft_strcmp(av[i], "-c")))
			tl->col = 1;
		else if (!(ft_strcmp(av[i], "-w")))
			tl->show_ways = 1;
		else if (!(ft_strcmp(av[i], "-a")))
			tl->show_ants = 1;
		else if (!(ft_strcmp(av[i], "-l")))
			tl->leaks = 1;
		else if (!(ft_strcmp(av[i], "-e")))
			tl->ants_home = 1;
		i++;
	}
}

int			main(int ac, char **av)
{
	t_lemin		*tl;
	t_way		*tw;
	t_room	*tv;
	t_ant		**ant_arr;

	tl = make_lemin();
	do_flags(ac, av, tl);
	tv = parsing(tl);
	tw = alg_and_sth_else(tv);
	ant_arr = ants_init(tl, tw);
	assign_ways(tl, ant_arr, tw);
	if (tl->show_ways)
		print_ways(tv, tw, tl);
	assign_rooms(tl, ant_arr, tv);
	tl->gone_ants = 0;
	while (tl->gone_ants < tl->ant_num)
		make_step(tl, ant_arr, tv);
	if (tl->leaks)
		system("leaks -quiet lem-in");
	return (0);
}
