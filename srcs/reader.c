/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:03:25 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/22 15:43:08 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "libft.h"
#include "reader.h"

/*
** Reads from a file descriptor.
** If the file descriptor represents STDIN and `read` returned a zero value,
** we set the reader as finished.
*/

static ssize_t		reader_read_fd(t_reader *reader)
{
	const int	fd = reader->ctx.fd.fd;
	ssize_t		nbytes;

	if ((nbytes = read(fd, reader->buffer, BUFF_SIZE)) == -1)
		return (-1);
	reader->index = 0;
	reader->length = nbytes;
	if (nbytes == 0 && fd == STDIN_FILENO)
		reader->finished = true;
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

t_reader			create_reader_fd(int fd, char *filename, bool auto_print)
{
	return ((t_reader) {
		.index = 0,
		.length = 0,
		.type = READER_TYPE_FD,
		.ctx.fd.fd = fd,
		.ctx.fd.filename = filename,
		.ctx.fd.auto_print = auto_print,
		.finished = false,
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
		.finished = false,
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
