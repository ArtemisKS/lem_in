/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:54:15 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 07:50:54 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*add_room(char **room_n, t_room *node, char stend)
{
	t_room		*room;
	static int	i = 0;

	room = init_room();
	room->name = ft_strdup(room_n[0]);
	room->x = ft_atoi(room_n[1]);
	room->y = ft_atoi(room_n[2]);
	room->id = i + 1;
	if (stend == 'e')
		room->beg = -1;
	else if (stend == 's')
		room->beg = 1;
	else
		room->beg = 0;
	if (!i)
		node = room;
	else
		ft_vpush(&node, room);
	i++;
	free_arr((void **)room_n);
	return (node);
}

bool			parse_links(char **room_n, t_room *node, char *str)
{
	int				i;

	i = -1;
	free_arr((void **)room_n);
	if (valid_link(str, &room_n, node))
	{	
		free_arr((void **)room_n);
		process_links(str, node);
		while (gl->map[++i])
			ft_putendl(gl->map[i]);
		ft_putchar('\n');
		return (false);
	}
	else
		puterr("Error: wrong room/first link");
	return (true);
}

t_room		*parse_val_rooms(char *str)
{
	static char		stend = 0;
	static t_room	*node = NULL;
	char			**room_n;
	int				hstend;

	while (get_next_line(gl->fd, &str) > 0 && realloc_darr(gl))
	{
		gl->map[gl->iter++] = str;
		if ((hstend = handle_stend(str, &stend)) == -1)
			continue ;
		else if (!hstend)
			break ;
		if (valid_room(str, &room_n, node))
			node = add_room(room_n, node, stend);
		else if (!parse_links(room_n, node, str))
			break ;
		stend = 0;
	}
	return (node);
}

void			form_links(t_room *room, char **l_arr)
{
	t_room	*child;
	t_room	*node;

	child = room;
	node = room;
	if (ft_strequ(l_arr[0], l_arr[1]))
	{
		free_arr((void **)l_arr);
		return ;
	}
	while (!ft_strequ(l_arr[0], room->name))
		room = room->next;
	while (!ft_strequ(l_arr[1], child->name))
		child = child->next;
	room->links[room->n_links++] = child;
	room->links[room->n_links] = NULL;
	child->links[child->n_links++] = room;
	child->links[child->n_links] = NULL;
	room = node;
	free_arr((void **)l_arr);
}

void			process_links(char *str, t_room *room)
{
	char	**link;
	int		i;

	link = NULL;
	i = 0;
	while (!i || (get_next_line(gl->fd, &str) > 0 && realloc_darr(gl)))
	{
		(i) ? gl->map[gl->iter++] = str : NULL;
		if (!(ft_strlen(str)))
			break ;
		else if (COMMENT(str))
			continue;
		else if (N_LETTER_L(str) && valid_link(str, &link, room))
			form_links(room, link);
		else
			puterr("Error: wrong link");
		i++;
	}
	if (str)
		ft_strdel(&str);
}
