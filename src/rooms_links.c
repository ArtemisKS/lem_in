/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:54:15 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 04:37:00 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*add_room(char **name, t_room *node, int fl)
{
	t_room	*tv;
	static int	i = 0;

	tv = make_struct();
	tv->name = ft_strdup(name[0]);
	tv->x = ft_atoi(name[1]);
	tv->y = ft_atoi(name[2]);
	free_arr((void **)name);
	tv->id = i + 1;
	if (!fl)
		tv->beg = -1;
	else if (fl == 1)
		tv->beg = 1;
	else
		tv->beg = 0;
	if (!i)
		node = tv;
	else
		ft_vpush(&node, tv);
	i++;
	return (node);
}

int				do_links(char **name, t_room *node, char *line, t_global *tl)
{
	int				i;

	free_arr((void **)name);
	if (link_correct(line, &name, node))
	{
		free_arr((void **)name);
		read_links(line, tl, node);
		i = -1;
		while (tl->map[++i])
			ft_printf("%s\n", tl->map[i]);
		ft_printf("\n");
		return (0);
	}
	else
		puterr("Error: wrong room/first link");
	return (1);
}

t_room		*read_rooms(char *line, t_global *tl)
{
	static int		fl = -1;
	static t_room	*node = NULL;
	char			**name;
	static int		beg = 0;
	static int		end = 0;

	while (get_next_line(tl->fd, &line) > 0 && realloc_darr(tl))
	{
		tl->map[tl->iter++] = line;
		if (room_exception(line, &beg, &end, &fl) == 1)
			continue;
		else if (!room_exception(line, &beg, &end, &fl))
			break ;
		if (room_correct(line, &name, node))
			node = add_room(name, node, fl);
		else if (!do_links(name, node, line, tl))
			break ;
		fl = -1;
	}
	return (node);
}

void			form_links(t_room *tv, char **link)
{
	t_room	*kid;
	t_room	*tmp;

	kid = tv;
	tmp = tv;
	if (!(ft_strcmp(link[0], link[1])))
	{
		free_arr((void **)link);
		return ;
	}
	while (ft_strcmp(link[0], tv->name))
		tv = tv->next;
	while (ft_strcmp(link[1], kid->name))
		kid = kid->next;
	tv->links[tv->n_links++] = kid;
	tv->links[tv->n_links] = NULL;
	kid->links[kid->n_links++] = tv;
	kid->links[kid->n_links] = NULL;
	tv = tmp;
	free_arr((void **)link);
}

void			read_links(char *line, t_global *tl, t_room *tv)
{
	char	**link;
	int		i;

	link = NULL;
	i = 0;
	while ((!i || get_next_line(tl->fd, &line) > 0) && realloc_darr(tl))
	{
		if (i)
			tl->map[tl->iter++] = line;
		if (!(ft_strlen(line)))
			break ;
		else if (line && line[0] == '#')
			continue;
		else if (line && line[0] != 'L' && link_correct(line, &link, tv))
			form_links(tv, link);
		else
			puterr("Error: wrong link");
		i++;
	}
	if (line)
		ft_strdel(&line);
}
