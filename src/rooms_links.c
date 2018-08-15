/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:54:15 by akupriia          #+#    #+#             */
/*   Updated: 2018/06/03 19:54:16 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vertex		*add_room(char **name, t_vertex *node, int fl)
{
	t_vertex	*tv;
	static int	i = 0;

	tv = make_struct();
	tv->name = ft_strdup(name[0]);
	tv->x = ft_atoi(name[1]);
	tv->y = ft_atoi(name[2]);
	free_arr((void **)name);
	tv->id = i + 1;
	if (!fl)
		tv->start = -1;
	else if (fl == 1)
		tv->start = 1;
	else
		tv->start = 0;
	if (!i)
		node = tv;
	else
		ft_vpush(&node, tv);
	i++;
	return (node);
}

int				do_links(char **name, t_vertex *node, char *line, t_lemin *tl)
{
	int				i;

	free_arr((void **)name);
	if (link_correct(line, &name, node))
	{
		free_arr((void **)name);
		read_links(line, tl, node);
		i = -1;
		while (tl->print[++i])
			ft_printf("%s\n", tl->print[i]);
		ft_printf("\n");
		return (0);
	}
	else
		ft_error(4);
	return (1);
}

t_vertex		*read_rooms(char *line, t_lemin *tl)
{
	static int		fl = -1;
	static t_vertex	*node = NULL;
	char			**name;
	static int		start = 0;
	static int		end = 0;

	while (get_next_line(tl->fd, &line) > 0 && str_arr_remalloc(tl))
	{
		tl->print[tl->it++] = line;
		if (room_exception(line, &start, &end, &fl) == 1)
			continue;
		else if (!room_exception(line, &start, &end, &fl))
			break ;
		if (room_correct(line, &name, node))
			node = add_room(name, node, fl);
		else if (!do_links(name, node, line, tl))
			break ;
		fl = -1;
	}
	return (node);
}

void			form_links(t_vertex *tv, char **link)
{
	t_vertex	*kid;
	t_vertex	*tmp;

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
	tv->kids[tv->kids_num++] = kid;
	tv->kids[tv->kids_num] = NULL;
	kid->kids[kid->kids_num++] = tv;
	kid->kids[kid->kids_num] = NULL;
	tv = tmp;
	free_arr((void **)link);
}

void			read_links(char *line, t_lemin *tl, t_vertex *tv)
{
	char	**link;
	int		i;

	link = NULL;
	i = 0;
	while ((!i || get_next_line(tl->fd, &line) > 0) && str_arr_remalloc(tl))
	{
		if (i)
			tl->print[tl->it++] = line;
		if (!(ft_strlen(line)))
			break ;
		else if (line && line[0] == '#')
			continue;
		else if (line && line[0] != 'L' && link_correct(line, &link, tv))
			form_links(tv, link);
		else
			ft_error(5);
		i++;
	}
	if (line)
		ft_strdel(&line);
}
