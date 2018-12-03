/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_a_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:25:39 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 03:25:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static bool			valid_room_coord(char ***room_n, t_room *room)
{
	int i;
	int j;

	i = 0;
	while ((*room_n)[++i] && !(j = 0))
	{
		if (!(*room_n)[i] || ((*room_n)[i][j] == '0' && (*room_n)[i][j + 1]))
			return (false);
		while ((*room_n)[i][j])
			if (!(ft_isdigit((*room_n)[i][j++])))
				return (false);
	}
	if ((*room_n)[0][ft_strlen((*room_n)[0]) - 1] == '-'
		|| (*room_n)[0][0] == '-')
		return (false);
	while (room)
	{
		if ((room->x == ft_atoi((*room_n)[1])
		&& room->y == ft_atoi((*room_n)[2]))
		|| (ft_strequ(room->name, (*room_n)[0])))
			return (false);
		room = room->next;
	}
	return (true);
}

bool				valid_room(char *str, char ***room_n, t_room *room)
{
	int cnt;
	int cnt1;
	int i;

	i = -1;
	cnt = 0;
	cnt1 = 0;
	*room_n = ft_strsplit(str, ' ');
	if (str[0] == 'L' || COMMENT(str))
		return (false);
	while (str[++i])
	{
		if (str[i] != ' ' && str[i + 1] && str[i + 1] == ' ')
			cnt++;
		if (str[i] == ' ')
			cnt1++;
	}
	if (cnt != 2 || cnt1 != 2 || !valid_room_coord(room_n, room))
		return (false);
	return (true);
}

static inline bool	valid_link_cycle(char ***links, t_room *room, t_room *tmp)
{
	int		j;

	j = -1;
	while (++j < 2)
	{
		while (tmp)
		{
			if (ft_strequ(tmp->name, (*links)[j]))
				return (true);
			tmp = tmp->next;
		}
		tmp = room;
	}
	return (false);
}

bool				valid_link(char *str, char ***links, t_room *room)
{
	int			cnt;
	t_room		*tmp;
	int			i;

	i = -1;
	cnt = 0;
	tmp = room;
	*links = ft_strsplit(str, '-');
	if (!(*links)[0] || !(*links)[1])
		return (false);
	while (str[++i])
		if (str[i] == '-')
			cnt++;
	if (!valid_link_cycle(links, room, tmp) || cnt != 1)
		return (false);
	return (true);
}

int					handle_stend(char *str, char *stend)
{
	if ((ft_strequ(str, "##end") && g_gl->has_end)
	|| (ft_strequ(str, "##start") && g_gl->has_start))
		puterr("Error: double start / end");
	else if (ft_strequ(str, "##start") && !(g_gl->has_start) && (*stend = 's')
		&& (g_gl->has_start = true))
		return (-1);
	else if (ft_strequ(str, "##end") && !(g_gl->has_end) && (*stend = 'e')
		&& (g_gl->has_end = true))
		return (-1);
	else if (COMMENT(str))
		return (-1);
	return (!(ft_strlen(str)) ? (0) : (1));
}
