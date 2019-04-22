/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:51:23 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/22 13:27:30 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (s[start])
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[len] = '\0';
	return (res);
}
