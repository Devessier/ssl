/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256_algo.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:58:54 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 13:59:56 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAC_SHA256_ALGO_H
# define HMAC_SHA256_ALGO_H
# include "ssl.h"

void		hmac_sha256_algo(t_context *ctx, t_reader *reader);

#endif
