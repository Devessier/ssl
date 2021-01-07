/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:43:49 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 20:45:14 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_ALGO_H
# define SHA512_ALGO_H
# include <stdint.h>
# include "ssl.h"
# include "reader.h"

typedef	__uint128_t	t_uint128;

void				sha512_algo(t_context *ctx, t_reader *reader);

#endif
