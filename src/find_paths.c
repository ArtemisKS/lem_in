/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 08:59:07 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 09:15:41 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		links_marked(t_room *room)
{
	int i;

	i = 0;
	while (room->links[i])
	{
		if (!room->links[i]->marked && !room->links[i]->used)
			return (0);
		i++;
	}
	return (1);
}

static inline void	calibrate_dist(t_room *room)
{
	t_room		*node;
	int			i;

	while (room)
	{
		i = 0;
		node = room;
		while (room && ++i)
			room = room->father;
		room = node;
		room->distance = i;
		room = room->next;
	}
}

t_path				*det_way(t_room *room)
{
	t_path		*path;
	t_room		*node;
	int			i;

	i = 0;
	path = ft_memalloc(sizeof(t_path));
	calibrate_dist(room);
	node = room;
	while (room && room->beg != -1)
		room = room->next;
	path->path = ft_memalloc(sizeof(int) * room->distance);
	path->distance = room->distance;
	while (room)
	{
		path->path[i++] = room->id;
		room = room->father;
		(room && room->father) ? room->used = 1 : 1;
	}
	path->n_ants = 0;
	path->next = NULL;
	room = node;
	(!(st_end_nearby(room))) ? bzero_room(room) : 1;
	return (path);
}

int		realloc_darr()
{
	static	int		iter = 1;
	char			**printcpy;
	int				i;

	if (iter == 1 || gl->map[BUFF] != NULL)
	{
		gl->n_lines = BUFF * iter;
		printcpy = ft_memalloc(sizeof(char *) * (gl->n_lines + 1));
		gl->n_lines -= BUFF;
		i = -1;
		while (++i < gl->n_lines)
			printcpy[i] = gl->map[i];
		i = -1;
		if (iter != 1)
			free(gl->map);
		else
			gl->iter = 0;
		gl->map = printcpy;
		iter++;
	}
	return (1);
}

bool		check_n_emm(char *line)
{
	if (!(ft_strlen(line)))
		puterr("Error: empty line before number of ants");
	if (ft_strequ(line, "##start"))
		puterr("Error: ##start before number of ants");
	else if (ft_strequ(line, "##end"))
		puterr("Error: ##end before number of ants");
	return (COMMENT(line) ? (false) : (true));
}
