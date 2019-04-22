/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:33:53 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/20 16:01:23 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		is_empty_room(t_ant *ants, int room_id, int antnum, int end_id)
{
	int i;

	i = -1;
	while (++i < antnum)
		if (ants[i].current_id == room_id && room_id != end_id)
			return (0);
	return (1);
}

int			move_and_print(t_data *data, t_ant *ants, int antnum)
{
	int i;
	int j;

	i = -1;
	while (++i < antnum)
	{
		if (ants[i].current_id == data->end_id)
			ants[i].is_out = 1;
		else if (is_empty_room(ants, ants[i].true_path[ants[i].i],
							antnum, data->end_id))
			ants[i].current_id = ants[i].true_path[ants[i].i++];
		else
			break ;
	}
	j = -1;
	while (++j < i)
	{
		if (ants[j].is_out == 0)
			ft_printf("L%d-%s ", ants[j].ant_id,
					data->rooms[ants[j].current_id].name);
	}
	return (ants[antnum - 1].is_out ? 0 : 1);
}

t_ant		*init_ants(t_data *data)
{
	t_ant	*ants;
	int		i;

	ants = (t_ant*)malloc(sizeof(t_ant) * data->number_of_ants);
	i = 0;
	while (i < data->number_of_ants)
	{
		ants[i].ant_id = i + 1;
		ants[i].is_out = 0;
		ants[i].i = 1;
		ants[i].current_id = data->start_id;
		ants[i].true_path =
			copy_path(data->true_paths[i % data->number_of_true_paths].path);
		i++;
	}
	return (ants);
}

void		free_ants(t_ant *ants, t_data *data)
{
	int i;

	i = -1;
	while (++i < data->number_of_ants)
		if (ants[i].true_path)
			free(ants[i].true_path);
	free(ants);
}

void		release_ants(t_data *data)
{
	t_ant	*ants;
	int		i;

	ants = init_ants(data);
	i = 0;
	while (i < data->map_i + 1)
		ft_printf("%s\n", data->map[i++]);
	while (1)
	{
		ft_printf("\n");
		if (!move_and_print(data, ants, data->number_of_ants))
			break ;
	}
	ft_printf("\n");
	free_ants(ants, data);
}
