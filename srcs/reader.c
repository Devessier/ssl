/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:03:25 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 12:38:20 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "libft.h"
#include "reader.h"

static size_t		reader_copy_to_buffer(t_reader *reader
	, char to_copy[BUFF_SIZE], size_t length)
{
	size_t	index;
	size_t	copied;
	char	character;

	if (reader->skip == NULL)
	{
		ft_memcpy(reader->buffer, to_copy, length);
		return (length);
	}
	index = 0;
	copied = 0;
	while (index < length)
	{
		character = to_copy[index];
		if (reader->skip(character) == false)
			reader->buffer[copied++] = character;
	}
	return (copied);
}

/*
** Reads from a file descriptor.
** If the file descriptor represents STDIN and `read` returned a zero value,
** we set the reader as finished.
*/

static ssize_t		reader_read_fd(t_reader *reader)
{
	const int	fd = reader->ctx.fd.fd;
	const bool	skip_active = reader->skip != NULL;
	char		buffer[BUFF_SIZE];
	ssize_t		nbytes;
	size_t		copied;

	if ((nbytes = read(fd
		, skip_active ? buffer : reader->buffer
		, BUFF_SIZE)) == -1)
		return (-1);
	if (skip_active)
		copied = reader_copy_to_buffer(reader, buffer, nbytes);
	else
		copied = nbytes;
	reader->index = 0;
	reader->length = copied;
	if (copied == 0 && fd == STDIN_FILENO)
		reader->finished = true;
	return (copied);
}

static ssize_t		reader_read_buffer(t_reader *reader)
{
	size_t	remaining;
	size_t	to_copy;
	size_t	copied;

	remaining = reader->ctx.buffer.data_length - reader->ctx.buffer.cursor;
	to_copy = remaining > BUFF_SIZE ? BUFF_SIZE : remaining;
	copied = reader_copy_to_buffer(reader
		, reader->ctx.buffer.data + reader->ctx.buffer.cursor
		, to_copy);
	reader->ctx.buffer.cursor += to_copy;
	reader->index = 0;
	reader->length = copied;
	return (copied);
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

t_reader			create_reader_empty()
{
	return ((t_reader) {
		.type = READER_TYPE_NOOP,
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
			return (ret < 0 ? ret : (ssize_t)copied);
		dest += remaining;
		length -= remaining;
		remaining = reader->length - reader->index;
	}
	ft_memcpy(dest, reader->buffer + reader->index, length);
	reader->index += length;
	return (length + copied);
}
