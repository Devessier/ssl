/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_flush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:41:35 by bdevessi          #+#    #+#             */
/*   Updated: 2021/05/04 21:01:41 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer.h"
#include "base64.h"
#include "libft.h"

void			writer_flush_internal(t_writer *writer)
{
	write(writer->fd, writer->buffer, writer->index);
	writer->index = 0;
}

static void		writer_flush_base64(t_writer *writer)
{
	uint8_t base64_encoded[BASE64_OUTPUT_BLOCK_LENGTH] = { 0 };

	if (writer->base64_buffer_index > 0)
	{
		base64_algo_encode((uint8_t *)writer->base64_buffer, writer->base64_buffer_index, base64_encoded);
		writer_write_fill_internal_buffer(writer, (char *)base64_encoded, sizeof(base64_encoded));
	}
	writer_flush_internal(writer);
}

void			writer_flush(t_writer *writer)
{
	if (writer->activated == false || writer->index == 0)
		return ;
	if (writer->base64_activated == true)
	{
		writer_flush_base64(writer);
		return ;
	}
	writer_flush_internal(writer);
}
