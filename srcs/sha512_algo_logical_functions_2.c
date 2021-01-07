/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo_logical_functions_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:56:09 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 00:00:54 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "algo_rotate.h"

uint64_t		ssig0_64(uint64_t x)
{
	return (rotr64(x, 1) ^ rotr64(x, 8) ^ (x >> 7));
}

uint64_t		ssig1_64(uint64_t x)
{
	return (rotr64(x, 19) ^ rotr64(x, 61) ^ (x >> 6));
}
