/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:08:41 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:47:45 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
# include <stdbool.h>
# include <unistd.h>
# define BUFF_SIZE 4096

enum				e_reader_type
{
	READER_TYPE_FD = 1,
	READER_TYPE_BUFFER
};

typedef struct		s_reader_fd_context
{
	int		fd;
	char	*filename;
	bool	auto_print;
}					t_reader_fd_context;

typedef struct		s_reader_buffer_context
{
	char	*data;
	size_t	data_length;
	size_t	cursor;
}					t_reader_buffer_context;

typedef union		u_reader_context
{
	t_reader_fd_context			fd;
	t_reader_buffer_context		buffer;
}					t_reader_context;

typedef bool		(*t_skipper_fn)(char character);

typedef struct		s_reader
{
	char				buffer[BUFF_SIZE];
	size_t				index;
	size_t				length;
	bool				finished;
	ssize_t				(*fill)(struct s_reader *reader);

	enum e_reader_type	type;
	t_reader_context	ctx;
}					t_reader;

t_reader			create_reader_fd(int fd, char *filename, bool auto_print);
t_reader			create_reader_buffer(char *buffer, size_t buffer_length);
t_reader			create_reader_empty();
ssize_t				reader_read(t_reader *reader, char *dest, size_t length);
ssize_t				reader_read_skip(
	t_reader *reader
	, char *dest
	, size_t length
	, t_skipper_fn skip);

#endif
