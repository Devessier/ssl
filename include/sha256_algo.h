/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:34:55 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 13:03:16 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_ALGO_H
# define SHA256_ALGO_H
# include <stdint.h>
# include "ssl.h"
# include "reader.h"

void		sha256_algo(t_context *ctx, t_reader *reader);

void		sha256_init(t_sha256_algo_context *ctx);
void		fill_sha256_states(t_sha256_states *to_fill
	, uint32_t intermediate_hash[8]);
void		add_sha256_states(uint32_t intermediate_hash[8]
	, t_sha256_states to_add);

uint32_t	ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t	maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t	bsig0(uint32_t x);
uint32_t	bsig1(uint32_t x);
uint32_t	ssig0(uint32_t x);
uint32_t	ssig1(uint32_t x);

#endif
