/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:39:01 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 14:10:06 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <stdint.h>
# include "ssl.h"
# include "reader.h"
# define MD5_BUFFER_SIZE 64

typedef struct	s_md5_states
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_md5_states;

typedef struct	s_md5_algo_context
{
	uint8_t			buffer[MD5_BUFFER_SIZE];
	size_t			buffer_length;

	t_md5_states	states;

	size_t			binary_length;

	uint32_t		permutation;
	uint32_t		word_index;
}				t_md5_algo_context;

void			bind_md5_args(t_context *ctx);
void			md5_algo(t_context *ctx, t_reader *reader);

#endif
