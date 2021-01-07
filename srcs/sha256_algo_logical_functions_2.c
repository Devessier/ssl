/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo_logical_functions_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:55:38 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 23:58:36 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "algo_rotate.h"

uint32_t		ssig0_32(uint32_t x)
{
	return (rotr32(x, 7) ^ rotr32(x, 18) ^ (x >> 3));
}

uint32_t		ssig1_32(uint32_t x)
{
	return (rotr32(x, 17) ^ rotr32(x, 19) ^ (x >> 10));
}
