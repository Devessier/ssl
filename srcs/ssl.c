/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:24:10 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/09 00:36:07 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "ssl.h"

static t_algo_desc	g_algo_descs[] = {
	{
		.algo = ALGO_MD5,
		.name = "md5"
	},
	{
		.algo = ALGO_SHA256,
		.name = "sha256"
	},
	{ 0 }
};

char				*get_algo_name(t_algo algo)
{
	t_algo_desc		*algo_desc;

	algo_desc = g_algo_descs;
	while (algo_desc->name != NULL) {
		if (algo_desc->algo == algo)
			return algo_desc->name;

		algo_desc++;
	}

	return NULL;
}
