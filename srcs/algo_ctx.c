/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 17:35:32 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 13:07:56 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ssl.h"
#include "digest.h"
#include "md5.h"
#include "sha256.h"

t_arg	*get_algo_arguments(t_algo algo)
{
	if (algo == ALGO_MD5 || algo == ALGO_SHA256)
		return (g_digest_arguments);
	return (NULL);
}
