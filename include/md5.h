/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:39:01 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/22 23:46:22 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <stdint.h>
# include "ssl.h"
# include "reader.h"
# define MD5_BUFFER_SIZE 64
# define MD5_HASH_SIZE 16

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

void			md5_algo(t_reader *reader, uint8_t hash[MD5_HASH_SIZE]);

#endif
