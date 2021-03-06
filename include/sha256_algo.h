/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:34:55 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 23:57:22 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_ALGO_H
# define SHA256_ALGO_H
# include <stdint.h>
# include "ssl.h"
# include "reader.h"

void		sha256_algo(t_context *ctx, t_reader *reader);
void		sha256_transform(t_sha256_algo_context *ctx);

void		sha256_init(t_sha256_algo_context *ctx);
void		fill_sha256_states(t_sha256_states *to_fill
	, uint32_t intermediate_hash[8]);
void		add_sha256_states(uint32_t intermediate_hash[8]
	, t_sha256_states to_add);

uint32_t	ch_32(uint32_t x, uint32_t y, uint32_t z);
uint32_t	maj_32(uint32_t x, uint32_t y, uint32_t z);
uint32_t	bsig0_32(uint32_t x);
uint32_t	bsig1_32(uint32_t x);
uint32_t	ssig0_32(uint32_t x);
uint32_t	ssig1_32(uint32_t x);

#endif
