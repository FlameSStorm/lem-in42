/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_deluxe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:01:30 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/18 14:01:32 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_start_end(t_room *rooms, char is_e)
{
	int i;
	int end;
	int start;

	end = 0;
	start = 0;
	i = -1;
	while (rooms[++i].name)
	{
		if (rooms[i].type == 1)
			start++;
		else if (rooms[i].type == -1)
			end++;
	}
	if (end != 1 || start != 1)
		print_error(0, "there should be 1 and only 1 start/end room", is_e);
}

int		check_ants(t_data *data)
{
	int i;
	int res;

	if (!data->map[0] || ft_strlen(data->map[0]) > 10)
		print_error(1, "Invalid ants or or ants string is too long",
			data->params.is_e);
	i = -1;
	while (data->map[0][++i])
		if (!ft_isdigit(data->map[0][i]))
			print_error(1, "Invalid ants", data->params.is_e);
	res = ft_atoi(data->map[0]);
	if (res < 1 || res > INT_MAX)
		print_error(2, "Invalid ants", data->params.is_e);
	return (res);
}

int		*copy_path(int const *path)
{
	int i;
	int *new;

	i = 0;
	while (path[i] != -1)
		i++;
	new = (int*)malloc(sizeof(int) * ++i);
	i = -1;
	while (path[++i] != -1)
		new[i] = path[i];
	new[i] = -1;
	return (new);
}

int		is_here(t_data *data, int id, int trigger)
{
	int i;
	int j;

	i = -1;
	while (++i < data->number_of_rooms + 10)
	{
		j = -1;
		while (++j < data->number_of_rooms + 10)
		{
			if (trigger == 0 && id == data->paths[i].path[j])
				return (1);
			if (trigger == 1 && id == data->true_paths[i].path[j])
				return (i);
		}
	}
	return (-1);
}

int		is_unique(t_data *data, int id)
{
	int i;

	i = -1;
	while (++i < data->number_of_rooms + 100)
		if (data->past_rooms[i] == id &&
			id != data->end_id && id != data->start_id)
			return (0);
	data->past_rooms[find_stack_len(data->past_rooms)] = id;
	return (1);
}
