/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 08:59:15 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 09:15:41 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool		is_int(char *str)
{
	int		ind;
	char	*int_max;

	int_max = "2147483647";
	if ((ind = ft_strlen(str)) > 10)
		return (true);
	if (ind == 10 && (ind == -1))
		while (str[++ind])
		{
			if (str[ind] == int_max[ind])
				continue ;
			return ((str[ind] > int_max[ind]) ? (false) : (true));
		}
	return (true);
}

t_path		*run_path_search(t_room *room)
{
	int				ind;
	static t_path	*tmp = NULL;
	static t_path	*path = NULL;

	ind = 0;
	while (!ind || stend_connected(room))
	{
		tmp = det_way(room);
		tmp->n_path = ind + 1;
		if (!ind)
			path = tmp;
		else
			ft_wpush(&path, tmp);
		if (!ind && st_end_nearby(room))
			break ;
		tmp = tmp->next;
		ind++;
	}
	while (room->beg != 1)
		room = room->next;
	room->occupied = 1;
	return (path);
}

t_emmet		**ants_init(t_path *path)
{
	int		i;
	t_path	*tmp;
	t_emmet	**ant_arr;

	i = 0;
	ant_arr = ft_memalloc(sizeof(t_emmet *) * gl->n_ants);
	while (i < gl->n_ants)
	{
		ant_arr[i] = ft_memalloc(sizeof(t_emmet));
		ant_arr[i]->room = NULL;
		ant_arr[i]->id = i + 1;
		i++;
	}
	tmp = path;
	i = 0;
	while (path)
	{
		i++;
		path->occupied = 0;
		path = path->next;
	}
	path = tmp;
	return (ant_arr);
}

static inline bool		assign_flags(char opt)
{
	const char			chars[5] = "acelw";
	const char			j[2] = {opt, 0};
	const size_t		index = ft_strstr(chars, j) - chars;
	int					res;

	res = 0;
	if (index < 5)
		((char *)(gl))[index] = true;
	else
		res = ft_printf("%s%c\n%s", "./lem_in: illegal option -- ", opt,
		"usage: ./lem_in [-acelw] < [file]\n");
	return (res != 0);
}

static inline int		parse_flags(int ac, char **av)
{
	int		i;
	int		k;

	i = 0;
	while ((++i < ac && (k = 1)) && (av[i][0] == '-' && av[i][1]))
		while (av[i][k])
			if (assign_flags(av[i][k++]))
				exit(1);
	return (1);
}

int						main(int ac, char **av)
{
	t_path		*path;
	t_room		*room;
	t_emmet		**ant_arr;

	gl = ft_memalloc(sizeof(t_global));;
	gl->ind = (ac > 1) ? (parse_flags(ac, av)) : 0;
	room = parse_validate(gl);
	path = run_path_search(room);
	ant_arr = ants_init(path);
	assign_ways(ant_arr, path);
	(gl->disp_paths) ? print_paths(room, path) : 1;
	assign_rooms(ant_arr, room);
	gl->n_ants_arr = 0;
	while (gl->n_ants_arr < gl->n_ants)
		make_step(ant_arr, room);
	(gl->colour || gl->ants_home) ? ft_putstr(RESET) : 1; 
	(gl->disp_leaks) ? system("leaks -quiet lem-in") : 1;
	return (0);
}
