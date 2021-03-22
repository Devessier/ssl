/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:04:13 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:44:47 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "writer.h"

t_writer	create_writer(int fd, char *filename)
{
	(void)filename;
	return ((t_writer){
		.index = 0,
		.bytes_written = 0,
		.activated = true,
		.fd = fd,
		.line_break = 0,
	});
}

t_writer	create_writer_breaker(int fd
	, char *filename
	, size_t line_break
	, char *new_line)
{
	t_writer	writer;

	writer = create_writer(fd, filename);
	writer.line_break = line_break;
	writer.new_line = new_line;
	writer.new_line_length = ft_strlen(new_line);
	return (writer);
}

t_writer	create_writer_empty(void)
{
	return ((t_writer){
		.activated = false,
	});
}
