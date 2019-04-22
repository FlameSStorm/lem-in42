/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:18:26 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/21 17:42:58 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	sym;
	int		i;

	i = 0;
	sym = (char)c;
	while (s[i] != sym)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return (char*)(&s[i]);
}
