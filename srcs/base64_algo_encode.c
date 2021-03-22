/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_algo_encode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:03:40 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:27:11 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "base64.h"

static void		base64_algo_encode_compute_sextets(
	uint8_t to_encode[BASE64_INPUT_BLOCK_LENGTH]
	, size_t to_encode_length
	, uint8_t sextets[BASE64_OUTPUT_BLOCK_LENGTH])
{
	sextets[0] = (to_encode[0] >> 2) & 0b111111;
	if (to_encode_length == 1)
		sextets[1] = ((to_encode[0] & 0b11) << 4);
	else
		sextets[1] = ((to_encode[0] & 0b11) << 4)
			| ((to_encode[1] >> 4) & 0b1111);
	if (to_encode_length == 2)
		sextets[2] = ((to_encode[1] & 0b1111) << 2);
	else if (to_encode_length == 1)
		sextets[2] = BASE64_PADDING_CHAR;
	else
		sextets[2] = ((to_encode[1] & 0b1111) << 2)
			| ((to_encode[2] >> 6) & 0b11);
	if (to_encode_length == 3)
		sextets[3] = to_encode[2] & 0b111111;
	else
		sextets[3] = BASE64_PADDING_CHAR;
}

static void		base64_algo_encode_sextets_to_octets(
	uint8_t sextets[BASE64_OUTPUT_BLOCK_LENGTH]
	, uint8_t dest[BASE64_OUTPUT_BLOCK_LENGTH])
{
	size_t	index;

	index = 0;
	while (index < BASE64_OUTPUT_BLOCK_LENGTH)
	{
		dest[index] = g_base64_dictionary[sextets[index]];
		index++;
	}
}

t_error			base64_algo_encode(
	uint8_t to_encode[BASE64_INPUT_BLOCK_LENGTH]
	, size_t to_encode_length
	, uint8_t dest[BASE64_OUTPUT_BLOCK_LENGTH])
{
	uint8_t		sextets[BASE64_OUTPUT_BLOCK_LENGTH];

	base64_algo_encode_compute_sextets(to_encode, to_encode_length, sextets);
	base64_algo_encode_sextets_to_octets(sextets, dest);
	return (E_SUCCESS);
}
