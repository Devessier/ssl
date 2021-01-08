/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:48 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 02:46:48 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_256_H
# define SHA512_256_H
# include "ssl.h"
# include "sha512.h"

typedef t_sha512_states			t_sha512_256_states;

typedef t_sha512_algo_context	t_sha512_256_algo_context;

void							bind_sha512_256_args(t_context *ctx);

#endif
