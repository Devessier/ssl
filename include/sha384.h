/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:48 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 00:56:01 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA384_H
# define SHA384_H
# include "ssl.h"
# include "sha512.h"

typedef t_sha512_states			t_sha384_states;

typedef t_sha512_algo_context	t_sha384_algo_context;

void							bind_sha384_args(t_context *ctx);

#endif
