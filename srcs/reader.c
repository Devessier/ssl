/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:03:25 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/11 11:40:25 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "reader.h"

static ssize_t		reader_read_fd(t_reader *reader)
{
	ssize_t		nbytes;

	if ((nbytes = read(reader->ctx.fd.fd, reader->buffer, BUFF_SIZE)) == -1)
		return (-1);
	reader->index = 0;
	reader->length = nbytes;
	return (nbytes);
}

static ssize_t		reader_read_buffer(t_reader *reader)
{
	size_t	remaining;
	size_t	to_copy;

	remaining = reader->ctx.buffer.data_length - reader->ctx.buffer.cursor;
	to_copy = remaining > BUFF_SIZE ? BUFF_SIZE : remaining;
	ft_memcpy(reader->buffer, reader->ctx.buffer.data
		+ reader->ctx.buffer.cursor, to_copy);
	reader->ctx.buffer.cursor += to_copy;
	reader->index = 0;
	reader->length = to_copy;
	return (to_copy);
}

t_reader			create_reader_fd(int fd)
{
	return ((t_reader) {
		.index = 0,
		.length = 0,
		.type = READER_TYPE_FD,
		.ctx.fd.fd = fd,
		.fill = reader_read_fd,
	});
}

t_reader			create_reader_buffer(char *buffer, size_t buffer_length)
{
	return ((t_reader) {
		.index = 0,
		.length = 0,
		.type = READER_TYPE_BUFFER,
		.ctx.buffer.data = buffer,
		.ctx.buffer.data_length = buffer_length,
		.ctx.buffer.cursor = 0,
		.fill = reader_read_buffer,
	});
}

ssize_t				reader_read(t_reader *reader, char *dest, size_t length)
{
	size_t	copied;
	size_t	remaining;
	ssize_t	ret;

	remaining = reader->length - reader->index;
	copied = 0;
	while (remaining < length)
	{
		copied += remaining;
		ft_memcpy(dest, reader->buffer + reader->index, remaining);
		if ((ret = reader->fill(reader)) <= 0)
			return (ret < 0 ? ret : copied);
		dest += remaining;
		length -= remaining;
		remaining = reader->length - reader->index;
	}
	ft_memcpy(dest, reader->buffer + reader->index, length);
	reader->index += length;
	return (length + copied);
}
