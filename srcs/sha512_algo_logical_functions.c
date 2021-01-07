/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo_logical_functions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:55:29 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 00:00:39 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "algo_rotate.h"

uint64_t		ch_64(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint64_t		maj_64(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint64_t		bsig0_64(uint64_t x)
{
	return (rotr64(x, 28) ^ rotr64(x, 34) ^ rotr64(x, 39));
}

uint64_t		bsig1_64(uint64_t x)
{
	return (rotr64(x, 14) ^ rotr64(x, 18) ^ rotr64(x, 41));
}
