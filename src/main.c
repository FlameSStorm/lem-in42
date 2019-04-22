/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:38:24 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/20 16:00:15 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	check_room(t_room *rooms, int j, char is_e)
{
	int		i;
	int		count;
	t_room	room;

	count = 0;
	room = rooms[j];
	i = -1;
	while (rooms[++i].name)
	{
		if (ft_strequ(rooms[i].name, room.name))
			count++;
		if (rooms[i].x == room.x && rooms[i].y == room.y && !count)
			print_error(123, "duplicate coordinates", is_e);
	}
	if (count > 1)
		print_error(6, "duplicate room name", is_e);
}

static	void	precheck_room(char **to_check, char is_e)
{
	if (!to_check || !to_check[0] || !to_check[1] || !to_check[2])
		print_error(3, "Invalid room", is_e);
	if (to_check[0][0] == 'L' || to_check[0][0] == '#')
		print_error(0, "room name shouldn't start with 'L' or '#'", is_e);
	if (ft_strlen(to_check[1]) > 10 || ft_strlen(to_check[2]) > 10 ||
			!is_digit_string(to_check[1]) || !is_digit_string(to_check[2]) ||
			ft_atoi(to_check[1]) < 0 || ft_atoi(to_check[2]) < 0)
		print_error(4, "Invalid coordinates", is_e);
}

static void		save_room(t_data *data, int i, short type)
{
	char		**room_data;
	static	int j = 0;

	if (!data->map[i])
		print_error(2, "incorrect ##start or ##end command", data->params.is_e);
	if (!(room_data = check_split(data->map[i], ' ', 3)))
		print_error(12, "invalid room line", data->params.is_e);
	precheck_room(room_data, data->params.is_e);
	data->rooms[j].name = ft_strdup(room_data[0]);
	data->rooms[j].x = ft_atoi(room_data[1]);
	data->rooms[j].y = ft_atoi(room_data[2]);
	data->rooms[j].type = type;
	if (data->rooms[j].type == 1)
		data->start_id = j;
	if (data->rooms[j].type == -1)
		data->end_id = j;
	data->rooms[j].id = j;
	data->rooms[++j].name = NULL;
	check_room(data->rooms, j - 1, data->params.is_e);
	ft_strdel(&room_data[0]);
	ft_strdel(&room_data[1]);
	ft_strdel(&room_data[2]);
	free(room_data);
}

static void		parse_all(t_data *data)
{
	int i;

	data->number_of_ants = check_ants(data);
	i = 0;
	while (data->map[++i])
	{
		if (data->map[i][0] == '#' && data->map[i][1] != '#')
			continue ;
		if (!ft_strchr(data->map[i], '#') && !ft_strchr(data->map[i], ' ') &&
			!ft_strchr(data->map[i], '-'))
			return ;
		if (ft_strequ(data->map[i], "##start") ||
			ft_strequ(data->map[i], "##end"))
			ft_strequ(data->map[i], "##start") ?
			save_room(data, ++i, STARTRM) : save_room(data, ++i, ENDRM);
		else if (ft_strchr(data->map[i], ' ') && data->map[i][0] != '#')
			save_room(data, i, REGULAR);
		else if (ft_strchr(data->map[i], '-'))
			RET_VOID(read_link(data, i));
		data->map_i = i;
	}
	check_start_end(data->rooms, data->params.is_e);
}

int				main(int ac, char const **av)
{
	t_data		data;
	int			ret;

	if (ac > 1)
		save_params(ac, av[1], &data);
	data.link_map = NULL;
	save_lines(&data);
	parse_all(&data);
	init_all(&data);
	ret = 1;
	data.only = 0;
	data.last = -1;
	init_paths_and_past_rooms(&data);
	while (ret == 1)
		ret = find_paths(&data);
	if (data.number_of_true_paths <= 0)
		print_error(2, "No solution", data.params.is_e);
	data.number_of_true_paths = data.params.is_o ? 1 :
		data.number_of_true_paths;
	release_ants(&data);
	while (ret < data.number_of_true_paths && data.params.is_p)
		print_path(&data, data.true_paths[ret++].path);
	return (0);
}
