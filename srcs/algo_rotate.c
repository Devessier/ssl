/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:30:42 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 17:59:34 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Shift operations in C are only defined for shift values which are
** not negative and smaller than sizeof(value) * CHAR_BIT.
** The mask, used with bitwise-and (&), prevents undefined behaviour
** when the shift count is 0 or >= the width of unsigned int.
*/

#include <stdint.h>
#include <limits.h>

uint32_t	rotl32(uint32_t value, unsigned int count)
{
	const unsigned int mask = CHAR_BIT * sizeof(value) - 1;

	count &= mask;
	return (value << count) | (value >> (-count & mask));
}

uint32_t	rotr32(uint32_t value, unsigned int count)
{
	const unsigned int mask = CHAR_BIT * sizeof(value) - 1;

	count &= mask;
	return (value >> count) | (value << (-count & mask));
}

uint64_t	rotl64(uint64_t value, unsigned int count)
{
	const unsigned int mask = CHAR_BIT * sizeof(value) - 1;

	count &= mask;
	return (value << count) | (value >> (-count & mask));
}

uint64_t	rotr64(uint64_t value, unsigned int count)
{
	const unsigned int mask = CHAR_BIT * sizeof(value) - 1;

	count &= mask;
	return (value >> count) | (value << (-count & mask));
}
