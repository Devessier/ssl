/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224_algo.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:53 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 01:48:10 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_224_ALGO_H
# define SHA512_224_ALGO_H
# include "ssl.h"
# include "reader.h"

void		sha512_224_algo(t_context *ctx, t_reader *reader);

#endif
