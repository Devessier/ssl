/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:38:57 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 14:49:38 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H
# include "ssl.h"
# include <stdint.h>
# define SHA256_WORDS_COUNT 16
# define SHA256_BUFFER_SIZE 64

typedef struct	s_sha256_states
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}				t_sha256_states;

typedef struct	s_sha256_algo_context
{
	uint8_t			buffer[SHA256_WORDS_COUNT * 4];
	size_t			buffer_length;

	uint32_t		intermediate_hash[8];

	size_t			binary_length;
}				t_sha256_algo_context;

void			bind_sha256_args(t_context *ctx);
void			sha256_cmd(t_context *ctx);

#endif
