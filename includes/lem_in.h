/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:02:35 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/20 20:46:53 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <limits.h>
# include <stdio.h>

# define RET_VOID(x) if (!(x)) return ;
# define REGULAR (0)
# define STARTRM (1)
# define ENDRM (-1)
# define NO_WAYS (-228)
# define WAY_FOUNDED (-1488)

# define ANSI_RED 			"\033[0;31m"
# define ANSI_BOLD_RED 		"\033[1;31m"
# define ANSI_GREEN 		"\033[0;32m"
# define ANSI_BOLD_GREEN 	"\033[1;32m"
# define ANSI_YELLLOW 		"\033[0;33m"
# define ANSI_BOLD_YELLOW	"\033[01;33m"
# define ANSI_BLUE	 		"\033[0;34m"
# define ANSI_BOLD_BLUE		"\033[1;34m"
# define ANSI_MAGEBTA		"\033[0;35m"
# define ANSI_BOLD_MAGENTA	"\033[1;35m"
# define ANSI_CYAN			"\033[0;36m"
# define ANSI_BOLD_CYAN		"\033[1;36m"
# define ANSI_RESET			"\033[0m"

typedef struct		s_param
{
	char			is_e;
	char			is_c;
	char			is_p;
	char			is_o;
}					t_param;

typedef struct		s_room
{
	int				id;
	int				x;
	int				y;
	char			*name;
	short			type;
}					t_room;

typedef struct		s_path
{
	int				top;
	int				*path;
}					t_path;

typedef struct		s_ant
{
	int				ant_id;
	int				i;
	char			is_out;
	int				current_id;
	int				*true_path;
}					t_ant;

typedef struct		s_data
{
	t_room			*rooms;
	t_ant			*ants;
	t_path			*paths;
	t_path			*true_paths;
	int				*past_rooms;
	int				*forbidden_rooms;
	char			**map;
	char			**link_map;
	char			**copy_of_link_map;
	int				number_of_ants;
	int				number_of_rooms;
	int				number_of_true_paths;
	int				start_id;
	int				end_id;
	int				only;
	int				last;
	int				map_i;
	t_param			params;
}					t_data;

char				read_link(t_data *data, int i);
void				print_error(int error_id, char *msg, char is_e);
void				save_number_of_rooms(t_data *data);
void				create_matrix(t_data *data);
int					find_paths(t_data *data);
char				**init_copy_of_link_map(char **link_map,
											int size, char is_e);
void				refresh_paths(t_data *data, int *stack);
int					find_stack_len(int const *stack);
void				print_path(t_data *data, int const *path);
void				print_link_map(t_data *data);
int					is_digit_string(char const *str);
int					*copy_path(int const *path);
void				release_ants(t_data *data);
void				print_usage(void);
void				save_lines(t_data *data);
void				init_all(t_data *data);
void				copy_lines_to_map(t_data *data, char **copy, int size);
void				save_params(int ac, char const *av, t_data *data);
void				check_start_end(t_room *rooms, char is_e);
int					check_ants(t_data *data);
int					is_unique(t_data *data, int id);
int					is_here(t_data *data, int id, int trigger);
int					*copy_path(int const *path);
char				write_to_path(t_data *data, int id, int prev_id,
	int stack_len);
void				save_true_path(t_data *data);
void				save_forbidden_rooms(t_data *data);
void				clear_data(t_data *data, int *stack);
char				**check_split(char *str, char c, int size);
void				init_paths_and_past_rooms(t_data *data);

#endif
