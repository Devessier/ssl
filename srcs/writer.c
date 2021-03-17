/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:04:13 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 01:36:21 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "writer.h"

static void		writer_write(t_writer *writer, char *to_write, size_t length)
{
	size_t	remaining;

	if (writer->activated == false)
		return ;
	remaining = WRITER_BUFF_SIZE - writer->index;
	while (remaining < length)
	{
		ft_memcpy(writer->buffer + writer->index, to_write, remaining);
		writer->flush(writer);
		to_write += remaining;
		length -= remaining;
		remaining = WRITER_BUFF_SIZE;
	}
	ft_memcpy(writer->buffer + writer->index, to_write, length);
	writer->index += length;
}

static void		writer_pad(t_writer *writer, char pad_char, size_t count)
{
	size_t	index;

	index = 0;
	while (index < count)
	{
		writer->write(writer, &pad_char, 1);
		index++;
	}
}

static void		writer_flush(t_writer *writer)
{
	if (writer->activated == false || writer->index == 0)
		return ;
	write(writer->fd, writer->buffer, writer->index);
	ft_bzero(writer->buffer, writer->index);
	writer->index = 0;
}

static void		writer_close(t_writer *writer)
{
	close(writer->fd);
	writer->activated = false;
}

t_writer		create_writer(int fd, char *filename)
{
	(void)filename;

	return ((t_writer){
		.index = 0,
		.activated = true,
		.fd = fd,
		.write = writer_write,
		.pad = writer_pad,
		.flush = writer_flush,
		.close = writer_close,
	});
}

t_writer		create_writer_empty()
{
	return ((t_writer){
		.activated = false,
	});
}
