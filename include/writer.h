/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:04:19 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:50:07 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITER_H
# define WRITER_H
# include <stdbool.h>
# include <unistd.h>
# define WRITER_BUFF_SIZE 4096

typedef struct			s_writer
{
	char			buffer[WRITER_BUFF_SIZE];
	size_t			index;
	size_t			bytes_written;
	bool			activated;

	int				fd;

	char			*new_line;
	size_t			new_line_length;
	size_t			line_break;
}						t_writer;

t_writer				create_writer(int fd, char *filename);
t_writer				create_writer_breaker(int fd
	, char *filename
	, size_t line_break
	, char *new_line);
t_writer				create_writer_empty();

void					writer_write(t_writer *writer
	, char *to_write
	, size_t length);
void					writer_pad(t_writer *writer
	, char pad_char
	, size_t count);
void					writer_flush(t_writer *writer);
void					writer_close(t_writer *writer);

#endif
