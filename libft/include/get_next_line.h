/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 14:26:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/15 12:44:14 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

# include "libft.h"

# define BUF_SIZE 8

int		get_next_line(int const fd, char **line);
char	*clear_tmp(char *tmp, int k);
char	*new_join(char *tmp, char *buf);
int		check_linefeed(char *s);

#endif
