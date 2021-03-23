/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256_algo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:38:42 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 14:07:49 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "ssl.h"

void			hmac_sha256_algo(t_context *ctx, t_reader *reader)
{
	(void)ctx;
	(void)reader;

	ft_putf("hi from hmac sha256 algo\n");
}
