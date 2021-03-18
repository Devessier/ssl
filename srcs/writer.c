/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:04:13 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/18 01:41:28 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "writer.h"

static void		writer_write_internal(t_writer *writer, char *to_write, size_t length)
{
	size_t	remaining;

	if (writer->activated == false)
		return ;
	writer->bytes_written += length;
	remaining = WRITER_BUFF_SIZE - writer->index;
	while (remaining < length)
	{
		ft_memcpy(writer->buffer + writer->index, to_write, remaining);
		writer->index += remaining;
		writer_flush(writer);
		to_write += remaining;
		length -= remaining;
		remaining = WRITER_BUFF_SIZE;
	}
	ft_memcpy(writer->buffer + writer->index, to_write, length);
	writer->index += length;
}

void			writer_write(t_writer *writer, char *to_write, size_t length)
{
	size_t	line_remainig;

	if (writer->activated == false)
		return ;
	if (writer->line_break == 0)
	{
		writer_write_internal(writer, to_write, length);
		return ;
	}
	line_remainig = writer->line_break - (writer->bytes_written % (writer->line_break + 1));
	while (line_remainig < length)
	{
		writer_write_internal(writer, to_write, line_remainig);
		writer_write_internal(writer, writer->new_line, writer->new_line_length);
		to_write += line_remainig;
		length -= line_remainig;
		line_remainig = writer->line_break - (writer->bytes_written % (writer->line_break + 1));
	}
	writer_write_internal(writer, to_write, length);
}

void			writer_pad(t_writer *writer, char pad_char, size_t count)
{
	size_t	index;

	index = 0;
	while (index < count)
	{
		writer_write(writer, &pad_char, 1);
		index++;
	}
}

void			writer_flush(t_writer *writer)
{
	if (writer->activated == false || writer->index == 0)
		return ;
	write(writer->fd, writer->buffer, writer->index);
	writer->index = 0;
}

void			writer_close(t_writer *writer)
{
	close(writer->fd);
	writer->activated = false;
}

t_writer		create_writer(int fd, char *filename)
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

t_writer				create_writer_breaker(int fd, char *filename, size_t line_break, char *new_line)
{
	t_writer	writer;

	writer = create_writer(fd, filename);
	writer.line_break = line_break;
	writer.new_line = new_line;
	writer.new_line_length = ft_strlen(new_line);
	return (writer);
}

t_writer		create_writer_empty()
{
	return ((t_writer){
		.activated = false,
	});
}
