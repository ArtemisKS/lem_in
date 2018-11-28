/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 23:44:45 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 00:23:45 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <libftprintf.h>

# define BUFF 30000

typedef struct		s_room
{
	unsigned int	marked : 1;
	unsigned int	occupied : 1;
	unsigned int	used : 1;
	int				distance;
	char			*name;
	int				id;
	int				beg;
	int				n_links;
	int				x;
	int				y;
	struct s_room	*father;
	struct s_room	**links;
	struct s_room *next;
}					t_room;

typedef struct		s_bfs
{
	t_room		*tv;
	struct s_bfs	*next;
}					t_bfs;

typedef struct		s_path
{
	int				*path;
	int				distance;
	unsigned int	occupied : 1;
	int				n_ants;
	int				n_path;
	struct s_path	*next;
}					t_path;

typedef struct		s_emmet
{
	int				id;
	struct s_path	*path;
	struct s_room *room;
}					t_emmet;

typedef struct		s_global
{
	unsigned int	colour : 1;
	unsigned int	disp_paths : 1;
	unsigned int	disp_emmets : 1;
	unsigned int	leaks : 1;
	int				n_ants;
	int				n_ants_arr;
	int				n_path;
	int				fd;
	unsigned int	ants_home : 1;
	unsigned int	it;
	char			**map;
	int				n_lines;
	int				gnl_ret;
}					t_global;

t_room				*make_struct();
t_global				*make_lemin();
t_room				*copy_kid(t_room *tv);
void				ft_error(int n);
void				free_arr(void **arr);
void				assign_rooms(t_global *tl, t_emmet **ant_arr, t_room *tv);
int					ft_min(int a, int b);
int					ant_can_go(t_global *tl, t_emmet *ant, t_room *tv);
int					antnum_cor(char *line);
void				null_vertex(t_room *tv);
int					check_links(t_room **tv, int distance, t_bfs **tq);
void				bfs_algo(t_room **tv, int *distance, \
					t_room *tmp, t_bfs **tq);
void				bfs(t_room *tv);
void				ft_vpush(t_room **alst, t_room *new);
void				ft_wpush(t_path **alst, t_path *new);
void				ft_qpush(t_bfs **tq, t_bfs *new);
t_bfs				*add_queue(t_room *tv, t_bfs *tq);
t_bfs				*pop_queue(t_bfs **tq);
int					links_marked(t_room *tv);
void				recalc_distance(t_room *tv);
t_path				*find_path(t_room *tv);
void				make_step(t_global *tl, t_emmet **ant_arr, t_room *tv);
int					beg_end_present(t_room *tv);
void				print_paths(t_room *tv, t_path *tw, t_global *tl);
int					beg_end_connected(t_room *tv);
t_room				*parsing(t_global *tl);
void				print_emmet(int ant_id, t_room *room, \
					int n_path, t_global *tl);
void				make_step_thing(t_global *tl, t_emmet **ant_arr, \
					t_room *tv, int ant_id);
void				output_emmets(t_global *tl, t_emmet **ant_arr, int ant_id);
int					room_correct(char *line, char ***name, t_room *tv);
int					link_correct(char *line, char ***name, t_room *tv);
int					room_exception(char *line, int *beg, int *end, int *fl);
t_room				*add_room(char **name, t_room *node, int fl);
int					do_links(char **name, t_room *node, \
					char *line, t_global *tl);
t_room				*read_rooms(char *line, t_global *tl);
void				form_links(t_room *tv, char **link);
t_room				*add_room(char **name, t_room *node, int fl);
void				read_links(char *line, t_global *tl, t_room *tv);
int					linked_with_end(t_room *tv);
int					assign_ways_sth(t_global *tl, t_path **tw);
int					assign_ways_thing(t_global *tl, t_path **tw, t_path *tmp);
void				assign_ways(t_global *tl, t_emmet **ant_arr, t_path *tw);
t_room				*make_rooms(t_path *tw, t_room *tv);
int					str_arr_remalloc(t_global *tl);
int					str_arr_remalloc(t_global *tl);
int					room_correct_3(char ***name, t_room *tv);
int					antsnum_exception(char *line);
int					int_value(char *line);

#endif
