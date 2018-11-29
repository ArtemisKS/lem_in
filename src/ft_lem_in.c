/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:35:29 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 15:48:30 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static inline int		file_is_val(const char *path)
{
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;
	return S_ISREG(st.st_mode);
}

static inline int		parse_flags(int ac, char **av)
{
	int		i;
	int		k;

	i = 0;
	while (++i < ac)
		if (av[i][0] == '-' && av[i][1] && (k = 1))
			while (av[i][k])
				if (assign_flags(av[i][k++]))
					exit(1);
	i = 0;
	k = 0;
	while (++i < ac)
		if (av[i][0] != '-')
			(file_is_val(av[i]) != -1) ? k++ : puterr("Invalid file in a parameter");
	return (k);
}

static t_room			*make_rooms(t_path *path, t_room *room)
{
	int			i;
	t_room		*res;
	t_room		*node;
	t_room		*way;

	node = room;
	res = link_cpy(room);
	i = path->distance - 1;
	while (--i >= 0)
	{
		room = node;
		while (room->next && path->path[i] != room->id)
			room = room->next;
		way = link_cpy(room);
		push_room(&res, way);
	}
	return (res);
}

int						main(int ac, char **av)
{
	t_path		*path;
	t_emmet		**arr_emm;
	t_room		*room;
	int			i;

	i = 0;
	gl = (t_global *)ft_memalloc(sizeof(t_global));
	if (ac > 1 && (gl->ind = parse_flags(ac, av)))
		while (++i < ac)
			if (av[i][0] != '-' && file_is_val(av[i]) != -1)
				if ((gl->fd = open(av[i], O_RDONLY)) == -1)
					puterr("File is somehow invalid");
	room = parse_validate();
	path = run_path_search(room);
	arr_emm = ants_init(path);
	det_paths(arr_emm, path);
	(gl->disp_paths) ? print_paths(room, path) : 1;
	i = -1;
	while (++i < gl->n_ants)
		arr_emm[i]->room = make_rooms(arr_emm[i]->path, room);
	gl->n_ants_arr = 0;
	while (gl->n_ants_arr < gl->n_ants)
		cond_one_st(arr_emm, room);
	(gl->colour || gl->ants_home) ? ft_putstr(RESET) : 1; 
	(gl->disp_leaks) ? system("leaks -q lem-in") : 1;
	return (0);
}
