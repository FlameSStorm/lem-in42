/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:04:07 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/20 19:51:42 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_error(int error_id, char *msg, char is_e)
{
	if (msg && is_e)
		ft_printf("ERROR:[%s]\n", msg);
	else
		ft_printf("ERROR\n");
	exit(error_id);
}

void		create_matrix(t_data *data)
{
	int i;
	int j;

	save_number_of_rooms(data);
	RET_VOID(data->link_map = (char**)malloc(sizeof(char*) *
		(data->number_of_rooms + 1)));
	RET_VOID(data->copy_of_link_map = (char**)malloc(sizeof(char*) *
		(data->number_of_rooms + 1)));
	i = -1;
	while (++i < data->number_of_rooms)
	{
		data->copy_of_link_map[i] = ft_strnew(data->number_of_rooms + 1);
		data->link_map[i] = ft_strnew(data->number_of_rooms + 1);
		j = -1;
		while (++j < data->number_of_rooms)
			data->link_map[i][j] = '0';
	}
	data->link_map[i] = NULL;
}

char		save_link(char *s1, char *s2, t_data *data)
{
	int i;
	int id1;
	int id2;

	i = -1;
	id1 = -1;
	id2 = -1;
	while (data->rooms[++i].name)
	{
		if (ft_strequ(s1, data->rooms[i].name))
			id1 = data->rooms[i].id;
		if (ft_strequ(s2, data->rooms[i].name))
			id2 = data->rooms[i].id;
	}
	if (id1 == -1 || id2 == -1 || id1 == id2 || data->link_map[id1][id2] == '1')
	{
		if (id1 == -1 || id2 == -1)
			ft_printf("ERROR:[link on non existing room]\n");
		id1 == id2 ? ft_printf("ERROR:[self link (disgusting)]\n") : 1;
		data->link_map[id1][id2] == '1' ? ft_printf("ERROR:[dup link]\n") : 1;
		return (0);
	}
	data->link_map[id1][id2] = '1';
	data->link_map[id2][id1] = '1';
	return (1);
}

void		save_number_of_rooms(t_data *data)
{
	int i;

	i = 0;
	while (data->rooms[i].name)
		i++;
	data->number_of_rooms = i;
}

char		read_link(t_data *data, int i)
{
	char		**link_data;
	int			ret;

	if (!data->link_map)
		create_matrix(data);
	if (!(link_data = check_split(data->map[i], '-', 2)))
	{
		ft_printf("ERROR:invalid link\n");
		return (0);
	}
	if (!link_data[0] || !link_data[1])
	{
		ft_printf("ERROR:link to nowhere\n");
		return (0);
	}
	ret = save_link(link_data[0], link_data[1], data);
	ft_strdel(&link_data[0]);
	ft_strdel(&link_data[1]);
	free(link_data);
	return (ret);
}
