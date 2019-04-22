/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:14:33 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/18 16:30:09 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_forbidden(t_data *data, int id)
{
	int i;

	i = -1;
	while (++i < data->number_of_rooms + 100)
		if (data->forbidden_rooms[i] != -1 && data->forbidden_rooms[i] == id)
			return (1);
	return (0);
}

void	remember_path(t_data *data, int const *stack, int prev_id)
{
	int i;

	if (data->only++ == 0)
		prev_id = data->start_id;
	i = -1;
	while (stack[++i] >= 0)
		if (is_here(data, stack[i], 0) == -1 &&
			data->link_map[stack[i]][prev_id] == '1')
			write_to_path(data, stack[i], prev_id, find_stack_len(stack));
}

int		*write_stack(t_data *data, int *stack)
{
	int i;
	int j;

	j = -1;
	i = stack[0] != -1 ? stack[0] : 0;
	stack = &stack[1];
	while (++j < data->number_of_rooms)
		if (data->copy_of_link_map[i][j] == '1' &&
			is_unique(data, j) && !is_forbidden(data, j))
		{
			data->copy_of_link_map[i][j] = '0';
			data->copy_of_link_map[j][i] = '0';
			stack[find_stack_len(stack)] = j;
			if (j == data->end_id)
			{
				if (write_to_path(data, data->end_id, i, 0))
					clear_data(data, stack);
				if (i == data->start_id && is_here(data, data->end_id, 3))
					stack[0] = NO_WAYS;
				return (stack);
			}
		}
	stack[0] = stack[0] == -1 ? NO_WAYS : stack[0];
	remember_path(data, stack, i);
	return (stack);
}

int		find_paths(t_data *data)
{
	int		*stack;
	int		*to_free;
	int		i;

	if (!data->link_map)
		print_error(123, "no links", data->params.is_e);
	stack = (int*)malloc(sizeof(int) * (data->number_of_rooms + 10));
	to_free = stack;
	refresh_paths(data, stack);
	i = -1;
	while (stack[0] != WAY_FOUNDED && ++i < data->number_of_rooms)
	{
		stack = write_stack(data, stack);
		if (stack[0] == NO_WAYS)
		{
			free(to_free);
			return (0);
		}
	}
	free(to_free);
	return (1);
}
