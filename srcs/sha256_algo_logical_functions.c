/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo_logical_functions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:55:04 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 23:58:33 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "algo_rotate.h"

uint32_t		ch_32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint32_t		maj_32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t		bsig0_32(uint32_t x)
{
	return (rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22));
}

uint32_t		bsig1_32(uint32_t x)
{
	return (rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25));
}
