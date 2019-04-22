/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_save_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:29:34 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/18 14:33:04 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		write_to_path(t_data *data, int id, int prev_id, int stack_len)
{
	int	i;

	i = -1;
	while (++i < data->number_of_rooms)
	{
		if (data->paths[i].top == prev_id && data->last != id)
		{
			data->paths[i].path[find_stack_len(data->paths[i].path)] = id;
			data->paths[i].top = id;
			data->last = stack_len != 1 ? id : data->last;
			if (stack_len != 1)
				return (1);
		}
	}
	if (stack_len)
		return (1);
	return (0);
}

void		save_true_path(t_data *data)
{
	int			i;
	static	int	k = 0;

	i = 0;
	while (data->paths[i].top != data->end_id && i < data->number_of_rooms)
		i++;
	if (i == data->number_of_rooms)
		print_error(0, "the way doesn't contain end!", data->params.is_e);
	data->true_paths[k].path = copy_path(data->paths[i].path);
	data->true_paths[k].top =
		data->true_paths[k].path[find_stack_len(data->true_paths[k].path)];
	data->number_of_true_paths = ++k;
}

void		save_forbidden_rooms(t_data *data)
{
	static int	k = 0;
	static int	j = 0;
	int			i;

	i = -1;
	while (++i < data->number_of_rooms + 1)
	{
		if (data->true_paths[j].path[i] == data->forbidden_rooms[i])
			i++;
		if (data->true_paths[j].path[i] != data->start_id &&
			data->true_paths[j].path[i] != data->end_id &&
			data->true_paths[j].path[i] != data->forbidden_rooms[i] &&
			data->true_paths[j].path[i] != -1)
			data->forbidden_rooms[k++] = data->true_paths[j].path[i];
	}
	j++;
}

void		init_paths_and_past_rooms(t_data *data)
{
	int k;

	data->paths = (t_path*)malloc(sizeof(t_path) *
		(data->number_of_rooms + 100));
	data->past_rooms = (int*)malloc(sizeof(int) *
		(data->number_of_rooms + 100));
	k = -1;
	while (++k < data->number_of_rooms + 100)
		data->paths[k].path = (int*)malloc(sizeof(int) *
			(data->number_of_rooms + 10));
}

void		clear_data(t_data *data, int *stack)
{
	int i;
	int j;

	save_true_path(data);
	stack[0] = WAY_FOUNDED;
	data->only = 0;
	data->last = -1;
	save_forbidden_rooms(data);
	i = -1;
	while (++i < 100)
	{
		data->past_rooms[i] = -1;
		data->paths[i].top = data->start_id;
		j = -1;
		while (++j < 100)
			data->paths[i].path[j] = -1;
		data->paths[i].path[0] = data->start_id;
	}
}
