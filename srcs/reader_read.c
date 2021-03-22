/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:38:02 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:40:24 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "reader.h"

ssize_t		reader_read_skip(t_reader *reader
	, char *dest, size_t length, t_skipper_fn skip)
{
	size_t	copied;
	ssize_t	ret;
	char	character;

	copied = 0;
	while (copied < length)
	{
		ret = reader_read(reader, &character, 1);
		if (ret < 0)
			return (ret);
		else if (ret == 0)
			return (copied);
		if (skip(character) == false)
			dest[copied++] = character;
	}
	return (copied);
}

ssize_t		reader_read(t_reader *reader, char *dest, size_t length)
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
