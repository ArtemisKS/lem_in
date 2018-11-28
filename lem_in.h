/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:49:29 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:36:01 by akupriia         ###   ########.fr       */
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
	int				dist;
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

typedef struct		s_queue
{
	t_room		*tv;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_way
{
	int				*way;
	struct s_way	*next;
	int				dist;
	int				ant_dist;
	unsigned int	occupied : 1;
	int				ant_num;
	int				way_num;
}					t_way;

typedef struct		s_ant
{
	int				id;
	struct s_way	*way;
	struct s_room *room;
}					t_ant;

typedef struct		s_lemin
{
	int				fd;
	int				ant_num;
	int				gone_ants;
	int				way_num;
	unsigned int	col : 1;
	unsigned int	show_ways : 1;
	unsigned int	show_ants : 1;
	unsigned int	leaks : 1;
	unsigned int	ants_home : 1;
	unsigned int	it;
	char			**print;
	int				sum;
	int				gnl;
}					t_lemin;

t_room			*make_struct();
t_lemin				*make_lemin();
t_room			*copy_kid(t_room *tv);
void				ft_error(int n);
void				free_arr(void **arr);
void				assign_rooms(t_lemin *tl, t_ant **ant_arr, t_room *tv);
int					ft_min(int a, int b);
int					ant_can_go(t_lemin *tl, t_ant *ant, t_room *tv);
int					antnum_cor(char *line);
void				null_vertex(t_room *tv);
int					check_links(t_room **tv, int dist, t_queue **tq);
void				bfs_algo(t_room **tv, int *dist, \
					t_room *tmp, t_queue **tq);
void				bfs(t_room *tv);
void				ft_vpush(t_room **alst, t_room *new);
void				ft_wpush(t_way **alst, t_way *new);
void				ft_qpush(t_queue **tq, t_queue *new);
t_queue				*add_queue(t_room *tv, t_queue *tq);
t_queue				*pop_queue(t_queue **tq);
int					links_marked(t_room *tv);
void				recalc_dist(t_room *tv);
t_way				*find_path(t_room *tv);
void				make_step(t_lemin *tl, t_ant **ant_arr, t_room *tv);
int					beg_end_present(t_room *tv);
void				print_ways(t_room *tv, t_way *tw, t_lemin *tl);
int					beg_end_connected(t_room *tv);
t_room			*parsing(t_lemin *tl);
void				print_ant(int ant_id, t_room *room, \
					int way_num, t_lemin *tl);
void				make_step_thing(t_lemin *tl, t_ant **ant_arr, \
					t_room *tv, int ant_id);
void				output_ants(t_lemin *tl, t_ant **ant_arr, int ant_id);
int					room_correct(char *line, char ***name, t_room *tv);
int					link_correct(char *line, char ***name, t_room *tv);
int					room_exception(char *line, int *beg, int *end, int *fl);
t_room			*add_room(char **name, t_room *node, int fl);
int					do_links(char **name, t_room *node, \
					char *line, t_lemin *tl);
t_room			*read_rooms(char *line, t_lemin *tl);
void				form_links(t_room *tv, char **link);
t_room			*add_room(char **name, t_room *node, int fl);
void				read_links(char *line, t_lemin *tl, t_room *tv);
int					linked_with_end(t_room *tv);
int					assign_ways_sth(t_lemin *tl, t_way **tw);
int					assign_ways_thing(t_lemin *tl, t_way **tw, t_way *tmp);
void				assign_ways(t_lemin *tl, t_ant **ant_arr, t_way *tw);
t_room			*make_rooms(t_way *tw, t_room *tv);
int					str_arr_remalloc(t_lemin *tl);
int					str_arr_remalloc(t_lemin *tl);
int					room_correct_3(char ***name, t_room *tv);
int					antsnum_exception(char *line);
int					int_value(char *line);

#endif
