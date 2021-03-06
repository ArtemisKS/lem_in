/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rms_lnks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:25:47 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 04:47:12 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

bool				parse_links(char **room_n, t_room *node, char *str)
{
	int				i;

	i = -1;
	memdel_arr((void **)room_n, ft_arrlen((void **)room_n));
	if (valid_link(str, &room_n, node))
	{
		memdel_arr((void **)room_n, ft_arrlen((void **)room_n));
		process_links(str, node);
		while (g_gl->map[++i])
			ft_putendl(g_gl->map[i]);
		ft_putchar('\n');
		return (false);
	}
	else
		puterr("Error: wrong room / first link");
	return (true);
}

t_room				*parse_val_rooms(char *str)
{
	static char		stend = 0;
	static t_room	*node = NULL;
	char			**room_n;
	int				hstend;
	int				gnl;

	while ((gnl = get_next_line(g_gl->fd, &str)) > 0 && realloc_darr())
	{
		g_gl->map[g_gl->iter++] = str;
		if ((hstend = handle_stend(str, &stend)) == -1)
			continue ;
		else if (!hstend)
			return (NULL);
		if (valid_room(str, &room_n, node))
			node = add_room(room_n, node, stend);
		else if (!parse_links(room_n, node, str))
			break ;
		stend = 0;
	}
	(gnl <= 0) ? puterr("Error: links are absent") : 1;
	return (node);
}

static void			write_children(t_room *room, char **l_arr)
{
	t_room	*child;
	t_room	*node;

	child = room;
	node = room;
	if (ft_strequ(l_arr[0], l_arr[1]))
	{
		memdel_arr((void **)l_arr, ft_arrlen((void **)l_arr));
		return ;
	}
	while (child && !ft_strequ(l_arr[1], child->name))
		child = child->next;
	while (room && !ft_strequ(l_arr[0], room->name))
		room = room->next;
	if (!room || !child)
		puterr("Error: room mentioned in links is not viable");
	room->links[room->n_links++] = child;
	room->links[room->n_links] = NULL;
	child->links[child->n_links++] = room;
	child->links[child->n_links] = NULL;
	room = node;
	memdel_arr((void **)l_arr, ft_arrlen((void **)l_arr));
}

void				process_links(char *str, t_room *room)
{
	char	**link;
	int		i;

	link = NULL;
	i = 0;
	while (!i || (get_next_line(g_gl->fd, &str) > 0 && realloc_darr()))
	{
		(i) ? g_gl->map[g_gl->iter++] = str : NULL;
		if (!(ft_strlen(str)))
			break ;
		else if (COMMENT(str))
			continue;
		else if (N_LETTER_L(str) && valid_link(str, &link, room))
			write_children(room, link);
		else
			puterr("Error: wrong link");
		i++;
	}
	(str) ? ft_strdel(&str) : 1;
}
