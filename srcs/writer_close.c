/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:41:34 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:42:40 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer.h"

void			writer_close(t_writer *writer)
{
	close(writer->fd);
	writer->activated = false;
}
