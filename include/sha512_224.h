/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:48 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 01:48:39 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_224_H
# define SHA512_224_H
# include "ssl.h"
# include "sha512.h"

typedef t_sha512_states			t_sha512_224_states;

typedef t_sha512_algo_context	t_sha512_224_algo_context;

void							bind_sha512_224_args(t_context *ctx);

#endif
