/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256_algo.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:53 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 02:46:33 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_256_ALGO_H
# define SHA512_256_ALGO_H
# include "ssl.h"
# include "reader.h"

void		sha512_256_algo(t_context *ctx, t_reader *reader);

#endif
