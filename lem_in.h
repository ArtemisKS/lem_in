/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 23:44:45 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 09:15:41 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <libftprintf.h>
# include <stdint.h>
# include <stdbool.h>

# define BUFF				30000
# define COMMENT(line)		(line && line[0] == '#')
# define N_LETTER_L(line)	(line && line[0] != 'L')
# define CYAN				"\033[0;36m"
# define YELLOW				"\033[0;33m"
# define BLUE				"\033[0;34m"
# define GREEN				"\033[1;32m"
# define PURPLE				"\033[0;35m"
# define RED				"\033[0;31m"
# define LRED				"\033[0;31m"
# define MAGENTA			"\033[0;35m"
# define BROWN				"\033[22;33m"
# define RESET				"\033[0m"


static const char	*g_col[] = {MAGENTA, RESET, BLUE, RED, YELLOW, CYAN,
	LRED, BROWN, NULL};
typedef struct		s_room
{
	unsigned int	marked : 1;
	unsigned int	occupied : 1;
	unsigned int	used : 1;
	int				distance;
	int				id;
	int				beg;
	int				n_links;
	int				x;
	int				y;
	char			*name;
	struct s_room	*father;
	struct s_room	**links;
	struct s_room	*next;
}					t_room;

typedef struct		s_bfs
{
	t_room			*room;
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
	char			disp_emmets;
	char			colour;
	char			ants_home;
	char			disp_leaks;
	char			disp_paths;
	int				n_ants;
	int				n_ants_arr;
	int				n_path;
	int				fd;
	unsigned int	iter;
	char			**map;
	int				n_lines;
	int				gnl_ret;
	int				ind;
	unsigned int	has_start : 1;
	unsigned int	has_end : 1;
}					t_global;

t_global			*gl;

t_room				*init_room();
t_room				*copy_kid(t_room *room);
void				puterr(const char *strerr);
void				free_arr(void **arr);
void				assign_rooms(t_emmet **ant_arr, t_room *room);
int					ft_min(int a, int b);
int					ant_can_go(t_emmet *ant, t_room *room);
bool				n_ants_valid(char *line);
void				bzero_room(t_room *room);
void				br_first_search(t_room *room);
void				ft_vpush(t_room **alst, t_room *new);
void				ft_wpush(t_path **alst, t_path *new);
t_bfs				*add_to_q(t_room *room, t_bfs *tq);
t_bfs				*pop_queue(t_bfs **tq);
int					links_marked(t_room *room);
t_path				*det_way(t_room *room);
void				make_step(t_emmet **ant_arr, t_room *room);
bool				stend_valid(t_room *room);
void				print_paths(t_room *room, t_path *path);
bool				st_end_nearby(t_room *room);
t_room				*parse_validate();
void				print_emmet(int id_emm, t_room *room,
					int n_path);
void				make_step_thing(t_emmet **ant_arr,
					t_room *room, int id_emm);
void				output_emmets(t_emmet **ant_arr, int id_emm);
bool				valid_room(char *line, char ***name, t_room *room);
bool				valid_link(char *line, char ***name, t_room *room);
int					handle_stend(char *line, char *stend);
t_room				*add_room(char **name, t_room *node, char stend);
bool				parse_links(char **name, t_room *node,
					char *line);
t_room				*parse_val_rooms(char *line);
void				form_links(t_room *room, char **link);
void				process_links(char *line, t_room *room);
bool				stend_connected(t_room *room);
int					assign_ways_sth(t_path **path);
int					assign_ways_thing(t_path **path, t_path *tmp);
void				assign_ways(t_emmet **ant_arr, t_path *path);
t_room				*make_rooms(t_path *path, t_room *room);
int					realloc_darr();
int					realloc_darr();
int					valid_room_3(char ***name, t_room *room);
bool				check_n_emm(char *line);
bool				is_int(char *line);

#endif
