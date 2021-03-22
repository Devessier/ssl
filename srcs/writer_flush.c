/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_flush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:41:35 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:42:24 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer.h"

void			writer_flush(t_writer *writer)
{
	if (writer->activated == false || writer->index == 0)
		return ;
	write(writer->fd, writer->buffer, writer->index);
	writer->index = 0;
}
