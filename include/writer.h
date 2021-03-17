/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:04:19 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 01:35:06 by bdevessi         ###   ########.fr       */
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
	bool			activated;

	int				fd;
	void			(*write)(struct s_writer *writer, char *to_write, size_t length);
	void			(*pad)(struct s_writer *writer, char pad_char, size_t count);
	void			(*flush)(struct s_writer *writer);
	void			(*close)(struct s_writer *writer);
}						t_writer;

t_writer				create_writer(int fd, char *filename);
t_writer				create_writer_empty();

#endif
