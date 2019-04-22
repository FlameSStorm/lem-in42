/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:52:38 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/25 20:16:05 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	refresh_paths(t_data *data, int *stack)
{
	int i;
	int j;

	i = -1;
	while (++i < data->number_of_rooms + 100)
	{
		data->past_rooms[i] = -1;
		j = -1;
		while (++j < data->number_of_rooms + 10)
			data->paths[i].path[j] = -1;
		data->paths[i].top = data->start_id;
		data->paths[i].path[0] = data->start_id;
	}
	i = -1;
	while (++i < data->number_of_rooms + 10)
		stack[i] = -1;
	i = -1;
	while (++i < data->number_of_rooms)
		ft_strcpy(data->copy_of_link_map[i], data->link_map[i]);
	stack[0] = data->start_id;
}

int		find_stack_len(int const *stack)
{
	int i;

	i = 0;
	while (stack[i] != -1)
		i++;
	return (i);
}

void	print_path(t_data *data, int const *path)
{
	int i;
	int j;

	i = -1;
	while (path[++i] >= 0)
	{
		j = -1;
		while (++j < data->number_of_rooms + 1)
			if (path[i] == data->rooms[j].id && data->rooms[j].name)
			{
				if (i != 0)
					printf(ANSI_CYAN"->");
				printf("%s%s", ANSI_BOLD_CYAN, data->rooms[j].name);
				if (data->rooms[j].type == 1)
					printf(ANSI_RED"(start)");
				else if (data->rooms[j].type == -1)
					printf(ANSI_GREEN"(end)");
			}
	}
	printf(ANSI_RESET);
	printf("\n");
}

int		is_digit_string(char const *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
