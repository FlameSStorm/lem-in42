/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:29:08 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/25 20:29:29 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**check_split(char *str, char c, int size)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count != size - 1 ? NULL : ft_strsplit(str, c));
}
