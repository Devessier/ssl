/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:41:36 by bdevessi          #+#    #+#             */
/*   Updated: 2021/05/04 21:02:23 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "writer.h"
#include "base64.h"

static void		writer_write_internal(
	t_writer *writer
	, char *to_write
	, size_t length)
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
		writer_flush_internal(writer);
		to_write += remaining;
		length -= remaining;
		remaining = WRITER_BUFF_SIZE;
	}
	ft_memcpy(writer->buffer + writer->index, to_write, length);
	writer->index += length;
}

void			writer_write_fill_internal_buffer(t_writer *writer, char *to_write, size_t length)
{
	size_t	line_remainig;

	line_remainig = writer->line_break - (writer->bytes_written
		% (writer->line_break + 1));
	while (line_remainig < length)
	{
		writer_write_internal(writer, to_write, line_remainig);
		writer_write_internal(writer, writer->new_line
			, writer->new_line_length);
		to_write += line_remainig;
		length -= line_remainig;
		line_remainig = writer->line_break - (writer->bytes_written
			% (writer->line_break + 1));
	}
	writer_write_internal(writer, to_write, length);
}

static void		writer_write_base64_internal(
	t_writer *writer,
	char *to_write,
	size_t length)
{
	size_t	remaining;
	uint8_t base64_to_encode[BASE64_INPUT_BLOCK_LENGTH] = { 0 };
	uint8_t base64_encoded[BASE64_OUTPUT_BLOCK_LENGTH] = { 0 };
	size_t	base64_to_encode_index;
	size_t	read_from_to_write;

	remaining = length + writer->base64_buffer_index;
	ft_memcpy(base64_to_encode, writer->base64_buffer, writer->base64_buffer_index);
	while (remaining >= 3)
	{
		base64_to_encode_index = writer->base64_buffer_index;
		read_from_to_write = sizeof(base64_to_encode) - base64_to_encode_index;
		ft_memcpy(base64_to_encode + base64_to_encode_index, to_write, sizeof(base64_to_encode));
		base64_algo_encode(base64_to_encode, sizeof(base64_to_encode), base64_encoded);
		writer_write_fill_internal_buffer(writer, (char *)base64_encoded, sizeof(base64_encoded));
		to_write += read_from_to_write;
		length -= read_from_to_write;
		writer->base64_buffer_index = 0;
		remaining = length + writer->base64_buffer_index;
	}
	ft_memcpy(writer->base64_buffer, to_write, length);
	writer->base64_buffer_index = length;
}

void			writer_write(t_writer *writer, char *to_write, size_t length)
{
	if (writer->activated == false)
		return ;
	if (writer->base64_activated == true)
	{
		writer_write_base64_internal(writer, to_write, length);
		return ;
	}
	if (writer->line_break == 0)
	{
		writer_write_internal(writer, to_write, length);
		return ;
	}
	writer_write_fill_internal_buffer(writer, to_write, length);
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
