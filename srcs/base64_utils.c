/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:00:14 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:01:03 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "writer.h"
#include "open.h"

t_writer					base64_create_writer(t_context *ctx
	, char *output_file, size_t line_break)
{
	int				file_fd;
	char			*filename;

	if (output_file == NULL)
	{
		file_fd = STDOUT_FILENO;
		filename = "stdout";
	}
	else
	{
		if ((file_fd = open_write_file(ctx, (char *)output_file)) == -1)
			return (create_writer_empty());
		filename = (char *)output_file;
	}
	if (line_break == 0)
		return (create_writer(file_fd, filename));
	return (create_writer_breaker(file_fd, filename, line_break, "\n"));
}
