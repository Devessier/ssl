/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:43:49 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 00:08:58 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_ALGO_H
# define SHA512_ALGO_H
# include <stdint.h>
# include "ssl.h"
# include "reader.h"

void		sha512_algo(t_context *ctx, t_reader *reader);

void		sha512_init(t_sha512_algo_context *ctx);
void		fill_sha512_states(t_sha512_states *to_fill
	, uint64_t intermediate_hash[8]);
void		add_sha512_states(uint64_t intermediate_hash[8]
	, t_sha512_states to_add);

uint64_t	ch_64(uint64_t x, uint64_t y, uint64_t z);
uint64_t	maj_64(uint64_t x, uint64_t y, uint64_t z);
uint64_t	bsig0_64(uint64_t x);
uint64_t	bsig1_64(uint64_t x);
uint64_t	ssig0_64(uint64_t x);
uint64_t	ssig1_64(uint64_t x);

#endif
