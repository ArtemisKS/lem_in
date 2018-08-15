/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:49:29 by akupriia          #+#    #+#             */
/*   Updated: 2018/05/03 15:49:30 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <libftprintf.h>

# define BUFF 30000

typedef struct		s_vertex
{
	struct s_vertex	*parent;
	struct s_vertex	**kids;
	struct s_vertex *next;
	unsigned int	visited : 1;
	unsigned int	busy : 1;
	unsigned int	taken : 1;
	int				dist;
	int				x;
	int				y;
	char			*name;
	int				id;
	int				start;
	int				kids_num;

}					t_vertex;

typedef struct		s_queue
{
	t_vertex		*tv;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_way
{
	int				*way;
	struct s_way	*next;
	int				dist;
	int				ant_dist;
	unsigned int	busy : 1;
	int				ant_num;
	int				way_num;
}					t_way;

typedef struct		s_ant
{
	int				id;
	struct s_way	*way;
	struct s_vertex *room;
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

t_vertex			*make_struct();
t_lemin				*make_lemin();
t_vertex			*copy_kid(t_vertex *tv);
void				ft_error(int n);
void				free_arr(void **arr);
void				assign_rooms(t_lemin *tl, t_ant **ant_arr, t_vertex *tv);
int					ft_min(int a, int b);
int					ant_can_go(t_lemin *tl, t_ant *ant, t_vertex *tv);
int					antnum_cor(char *line);
void				null_vertex(t_vertex *tv);
int					check_kids(t_vertex **tv, int dist, t_queue **tq);
void				bfs_algo(t_vertex **tv, int *dist, \
					t_vertex *tmp, t_queue **tq);
void				bfs(t_vertex *tv);
void				ft_vpush(t_vertex **alst, t_vertex *new);
void				ft_wpush(t_way **alst, t_way *new);
void				ft_qpush(t_queue **tq, t_queue *new);
t_queue				*add_queue(t_vertex *tv, t_queue *tq);
t_queue				*pop_queue(t_queue **tq);
int					kids_visited(t_vertex *tv);
void				recalc_dist(t_vertex *tv);
t_way				*find_path(t_vertex *tv);
void				make_step(t_lemin *tl, t_ant **ant_arr, t_vertex *tv);
int					start_end_present(t_vertex *tv);
void				print_ways(t_vertex *tv, t_way *tw, t_lemin *tl);
int					start_end_connected(t_vertex *tv);
t_vertex			*parsing(t_lemin *tl);
void				print_ant(int ant_id, t_vertex *room, \
					int way_num, t_lemin *tl);
void				make_step_thing(t_lemin *tl, t_ant **ant_arr, \
					t_vertex *tv, int ant_id);
void				output_ants(t_lemin *tl, t_ant **ant_arr, int ant_id);
int					room_correct(char *line, char ***name, t_vertex *tv);
int					link_correct(char *line, char ***name, t_vertex *tv);
int					room_exception(char *line, int *start, int *end, int *fl);
t_vertex			*add_room(char **name, t_vertex *node, int fl);
int					do_links(char **name, t_vertex *node, \
					char *line, t_lemin *tl);
t_vertex			*read_rooms(char *line, t_lemin *tl);
void				form_links(t_vertex *tv, char **link);
t_vertex			*add_room(char **name, t_vertex *node, int fl);
void				read_links(char *line, t_lemin *tl, t_vertex *tv);
int					linked_with_end(t_vertex *tv);
int					assign_ways_sth(t_lemin *tl, t_way **tw);
int					assign_ways_thing(t_lemin *tl, t_way **tw, t_way *tmp);
void				assign_ways(t_lemin *tl, t_ant **ant_arr, t_way *tw);
t_vertex			*make_rooms(t_way *tw, t_vertex *tv);
int					str_arr_remalloc(t_lemin *tl);
int					str_arr_remalloc(t_lemin *tl);
int					room_correct_3(char ***name, t_vertex *tv);
int					antsnum_exception(char *line);
int					int_value(char *line);

#endif
