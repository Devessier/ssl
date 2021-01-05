/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:34:55 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 17:04:19 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_ALGO_H
# define SHA224_ALGO_H
# include <stdint.h>
# include "ssl.h"
# include "sha224.h"
# include "reader.h"

void		sha224_algo(t_context *ctx, t_reader *reader);

void		fill_sha224_states(t_sha224_states *to_fill
	, uint32_t intermediate_hash[8]);
void		add_sha224_states(uint32_t intermediate_hash[8]
	, t_sha224_states to_add);

#endif
