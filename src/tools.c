/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:58:20 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/18 16:27:25 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_usage(void)
{
	printf(ANSI_BOLD_RED);
	printf("Usage: ./lem-in [-opue] < [file]\n");
	printf(ANSI_BOLD_GREEN);
	printf("o - only one path to move\n");
	printf(ANSI_BOLD_YELLOW);
	printf("p - print paths\n");
	printf(ANSI_BOLD_BLUE);
	printf("u - print usage\n");
	printf(ANSI_BOLD_CYAN);
	printf("e - print more info about error\n");
	printf(ANSI_RESET);
	exit(0);
}

void			save_params(int ac, char const *av, t_data *data)
{
	int	i;

	data->params.is_p = 0;
	data->params.is_c = 0;
	data->params.is_o = 0;
	data->params.is_e = 0;
	if (av[0] != '-' || ft_strlen(av) == 1 || ac > 2)
		print_usage();
	i = 0;
	while (av[++i])
		if (av[i] == 'u' || (av[i] != 'o' && av[i] != 'p' &&
							av[i] != 'e'))
			print_usage();
	i = 0;
	while (av[++i])
	{
		if (av[i] == 'p')
			data->params.is_p = 1;
		if (av[i] == 'o')
			data->params.is_o = 1;
		if (av[i] == 'c')
			data->params.is_c = 1;
		if (av[i] == 'e')
			data->params.is_e = 1;
	}
}

void			copy_lines_to_map(t_data *data, char **copy, int size)
{
	int	i;

	i = -1;
	data->map = (char**)malloc(sizeof(char*) * (size + 1));
	while (++i < size)
	{
		data->map[i] = ft_strdup(copy[i]);
		ft_strdel(&copy[i]);
	}
	data->map[i] = NULL;
	free(copy);
}

void			save_lines(t_data *data)
{
	int		i;
	char	**res;

	RET_VOID(res = (char**)malloc(sizeof(char*) * 100000));
	i = 0;
	while (get_next_line(0, &res[i]) > 0)
		i++;
	res[i] = NULL;
	data->rooms = (t_room*)malloc(sizeof(t_room) * i);
	copy_lines_to_map(data, res, i);
}

void			init_all(t_data *data)
{
	int i;

	data->forbidden_rooms = (int*)malloc(sizeof(int) *
		(data->number_of_rooms + 100));
	data->true_paths = (t_path*)malloc(sizeof(t_path) *
		(data->number_of_rooms + 10));
	i = -1;
	while (++i < data->number_of_rooms + 100)
		data->forbidden_rooms[i] = -1;
}
