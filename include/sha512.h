/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:55:16 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 17:05:08 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H
# include "ssl.h"
# include <stdint.h>
# define SHA512_WORDS_COUNT 16
# define SHA512_WORD_BYTES 8
# define SHA512_BUFFER_SIZE 128

typedef struct	s_sha512_states
{
	uint64_t	a;
	uint64_t	b;
	uint64_t	c;
	uint64_t	d;
	uint64_t	e;
	uint64_t	f;
	uint64_t	g;
	uint64_t	h;
}				t_sha512_states;

typedef struct	s_sha512_algo_context
{
	uint8_t			buffer[SHA512_WORDS_COUNT * SHA512_WORD_BYTES];
	size_t			buffer_length;

	uint64_t		intermediate_hash[8];

	size_t			binary_length;
}				t_sha512_algo_context;

void			bind_sha512_args(t_context *ctx);

#endif
