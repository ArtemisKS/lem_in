/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:25:20 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 04:46:38 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int						ft_arrlen(void **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

bool					is_int(char *str)
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

t_path					*run_path_search(t_room *room)
{
	int				ind;
	static t_path	*tmp = NULL;
	static t_path	*path = NULL;

	ind = 0;
	while (!ind || stend_connected(room))
	{
		tmp = det_way(room);
		tmp->n_path = ind + 1;
		g_gl->n_path++;
		if (!ind)
			path = tmp;
		else
			push_way(&path, tmp);
		if (!ind && st_end_nearby(room))
			break ;
		tmp = tmp->next;
		ind++;
	}
	return (path);
}

t_emmet					**ants_init(t_path *path)
{
	int		i;
	t_path	*tmp;
	t_emmet	**arr_emm;

	i = -1;
	arr_emm = ft_memalloc(sizeof(t_emmet *) * g_gl->n_ants);
	while (++i < g_gl->n_ants)
	{
		arr_emm[i] = ft_memalloc(sizeof(t_emmet));
		arr_emm[i]->room = NULL;
		arr_emm[i]->id = i + 1;
	}
	tmp = path;
	while (tmp && !(tmp->occupied = 0))
		tmp = tmp->next;
	return (arr_emm);
}
