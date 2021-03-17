/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_skip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:19:32 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 12:48:47 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

t_reader			create_reader_fd_skipper(int fd, char *filename
	, bool auto_print, skipper_fn skip)
{
	t_reader	reader;

	reader = create_reader_fd(fd, filename, auto_print);
	reader.skip = skip;
	return (reader);
}

t_reader			create_reader_buffer_skipper(char *buffer
	, size_t buffer_length, skipper_fn skip)
{
	t_reader	reader;

	reader = create_reader_buffer(buffer, buffer_length);
	reader.skip = skip;
	return (reader);
}

