/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo_logical_functions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:55:04 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 12:58:30 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "algo_rotate.h"

uint32_t		ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint32_t		maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t		bsig0(uint32_t x)
{
	return (rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22));
}

uint32_t		bsig1(uint32_t x)
{
	return (rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25));
}

uint32_t		ssig0(uint32_t x)
{
	return (rotr32(x, 7) ^ rotr32(x, 18) ^ (x >> 3));
}
