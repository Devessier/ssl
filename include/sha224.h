/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:14:39 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 16:35:33 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_H
# define SHA224_H
# include "ssl.h"
# include "sha256.h"

typedef t_sha256_states			t_sha224_states;

typedef	t_sha256_algo_context	t_sha224_algo_context;

void							bind_sha224_args(t_context *ctx);


#endif
