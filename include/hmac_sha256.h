/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:58:16 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 14:13:21 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAC_SHA256_H
# define HMAC_SHA256_H
# include "ssl.h"

void	bind_hmac_sha256_args(t_context *ctx);

#endif
