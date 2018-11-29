/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 21:14:50 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 04:25:09 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool		is_int(char *line)
{
	int		ind;
	char	*int_max;

	int_max = "2147483647";
	if ((ind = ft_strlen(line)) > 10)
		return (true);
	if (ind == 10 && (ind == -1))
		while (line[++ind])
		{
			if (line[ind] == int_max[ind])
				continue ;
			return ((line[ind] > int_max[ind]) ? (false) : (true));
		}
	return (true);
}

t_path		*alg_and_sth_else(t_room *tv)
{
	int		i;
	t_path	*tmp;
	t_path	*tw;

	i = 0;
	tmp = NULL;
	tw = NULL;
	while (!i || linked_with_end(tv))
	{
		tmp = find_path(tv);
		tmp->n_path = i + 1;
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

t_emmet		**ants_init(t_global *gl, t_path *tw)
{
	int		i;
	t_path	*tmp;
	t_emmet	**ant_arr;

	i = 0;
	ant_arr = (t_emmet **)malloc(sizeof(t_emmet *) * gl->n_ants);
	while (i < gl->n_ants)
	{
		ant_arr[i] = (t_emmet *)malloc(sizeof(t_emmet));
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

static inline bool		assign_flags(char opt, t_global *gl)
{
	const char			chars[5] = "acelw";
	const char			j[2] = {opt, 0};
	const size_t		index = ft_strstr(chars, j) - chars;
	int					res;

	res = 0;
	ft_printf("%c\n", opt);
	if (index < 5)
		((char *)(gl))[index] = true;
	else
		res = ft_printf("%s%c\n%s", "./lem_in: illegal option -- ", opt,
		"usage: ./lem_in [-acelw] < [file]\n");
	return (res != 0);
}

static inline int		parse_flags(int ac, char **av, t_global *gl)
{
	int		i;
	int		k;

	i = 0;
	while ((++i < ac && (k = 1)) && (av[i][0] == '-' && av[i][1]))
		while (av[i][k])
			if (assign_flags(av[i][k++], gl))
				exit(1);
	return (1);
}

int						main(int ac, char **av)
{
	t_global	gl;
	t_path		*tw;
	t_room		*tv;
	t_emmet		**ant_arr;

	// if (ac > 1) write(1, av[1], ft_strlen(av[1]));
	ft_bzero(&gl, sizeof(t_global *));
	gl.ind = (ac > 1) ? (parse_flags(ac, av, &gl)) : 0;
	tv = parse_validate(&gl);
	tw = alg_and_sth_else(tv);
	ant_arr = ants_init(&gl, tw);
	assign_ways(&gl, ant_arr, tw);
	// ft_printf("gl.disp_paths: %d\n", gl.disp_paths);
	if (gl.disp_paths)
		print_paths(tv, tw, &gl);
	assign_rooms(&gl, ant_arr, tv);
	gl.n_ants_arr = 0;
	while (gl.n_ants_arr < gl.n_ants)
		make_step(&gl, ant_arr, tv);
	if (gl.leaks)
		system("leaks -quiet lem-in");
	return (0);
}
