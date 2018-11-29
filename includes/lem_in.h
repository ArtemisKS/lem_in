/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:39:04 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 17:17:46 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <libftprintf.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define BUFF				10
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
	char			beg;
	int				distance;
	int				id;
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
	int				distance;
	int				n_ants;
	int				n_path;
	int				occupied;
	int				*path;
	struct s_path	*next;
}					t_path;

typedef struct		s_emmet
{
	int				id;
	struct s_path	*path;
	struct s_room	*room;
}					t_emmet;

typedef struct		s_global
{
	char			disp_emmets;
	char			colour;
	char			ants_home;
	char			disp_leaks;
	char			dsp_pths;
	int				n_ants;
	int				n_ants_arr;
	int				n_path;
	int				fd;
	unsigned int	iter;
	int				n_lines;
	int				gnl_ret;
	int				ind;
	unsigned int	has_start : 1;
	unsigned int	has_end : 1;
	char			**map;
}					t_global;

t_global			*g_gl;

t_room				*link_cpy(t_room *room);
void				puterr(const char *strerr);
int					ft_arrlen(void **arr);
void				assign_rooms(t_emmet **ant_arr, t_room *room);
int					ft_min(int a, int b);
bool				emm_may_move(t_emmet *ant, t_room *room);
bool				n_ants_valid(char *line);
void				bzero_room(t_room *room);
t_emmet				**ants_init(t_path *path);
void				br_first_search(t_room *room);
void				push_room(t_room **alst, t_room *new);
void				push_way(t_path **alst, t_path *new);
t_bfs				*add_to_q(t_room *room, t_bfs *tq);
t_bfs				*pop_q(t_bfs **tq);
t_path				*det_way(t_room *room);
void				cond_one_st(t_emmet **ant_arr, t_room *room);
bool				stend_valid(t_room *room);
t_path				*run_path_search(t_room *room);
bool				st_end_nearby(t_room *room);
t_room				*parse_validate(void);
void				print_emmet(int id_emm, t_room *room,
					int n_path);
void				cond_one_st_thing(t_emmet **ant_arr,
					t_room *room, int id_emm);
void				print_paths(t_room *room, t_path *path);
void				do_emm_printing(t_emmet **ant_arr, int id_emm);
bool				valid_room(char *line, char ***name, t_room *room);
bool				valid_link(char *line, char ***name, t_room *room);
int					handle_stend(char *line, char *stend);
t_room				*add_room(char **name, t_room *node, char stend);
bool				parse_links(char **name, t_room *node,
					char *line);
t_room				*parse_val_rooms(char *line);
void				process_links(char *line, t_room *room);
bool				stend_connected(t_room *room);
void				det_paths(t_emmet **ant_arr, t_path *path);
bool				realloc_darr(void);
bool				check_n_emm(char *line);
bool				is_int(char *line);

#endif
