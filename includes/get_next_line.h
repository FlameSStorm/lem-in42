/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:39:11 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/09/19 16:01:24 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <fcntl.h>

# define BUFF_SIZE 1
# define MCHECK(x) if (!x) return (-1)
# define CHECK_EOF(x) if (x) return (0)
# define CONTENT curr->content

int		get_next_line(const int fd, char **line);
int		ft_copyline(char **dest, char *src);

#endif
