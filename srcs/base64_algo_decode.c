/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_algo_decode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:03:38 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:23:36 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "base64.h"
#include "base64_algo.h"

static t_error		base64_algo_decode_characters_to_indexes(
	uint8_t to_decode[BASE64_OUTPUT_BLOCK_LENGTH])
{
	int8_t	decoded_character;
	size_t	index;

	index = 0;
	while (index < BASE64_OUTPUT_BLOCK_LENGTH)
	{
		if ((decoded_character = base64_decode_encoded_character(
				to_decode[index])) == -1)
			return (E_FAILURE);
		to_decode[index] = decoded_character;
		index++;
	}
	return (E_SUCCESS);
}

static void			base64_algo_decode_compute_sextets(
	uint8_t to_decode[BASE64_OUTPUT_BLOCK_LENGTH]
	, size_t input_block_length
	, uint8_t sextets[BASE64_OUTPUT_BLOCK_LENGTH])
{
	sextets[0] = to_decode[0] & 0b111111;
	if (input_block_length == 2)
		sextets[1] = to_decode[1] & 0b110000;
	else
		sextets[1] = to_decode[1] & 0b111111;
	if (input_block_length == 2)
		sextets[2] = BASE64_PADDING_CHAR;
	else if (input_block_length == 3)
		sextets[2] = to_decode[2] & 0b111100;
	else
		sextets[2] = to_decode[2] & 0b111111;
	if (input_block_length == 4)
		sextets[3] = to_decode[3] & 0b111111;
	else
		sextets[3] = BASE64_PADDING_CHAR;
}

static void			base64_algo_decode_sextets_to_octets(
	uint8_t sextets[BASE64_OUTPUT_BLOCK_LENGTH]
	, uint8_t dest[BASE64_INPUT_BLOCK_LENGTH])
{
	dest[0] = ((sextets[0] & 0b111111) << 2) | ((sextets[1] & 0b110000) >> 4);
	dest[1] = ((sextets[1] & 0b1111) << 4) | ((sextets[2] & 0b111100) >> 2);
	dest[2] = ((sextets[2] & 0b11) << 6) | (sextets[3] & 0b111111);
}

ssize_t				base64_algo_decode(
	uint8_t to_decode[BASE64_OUTPUT_BLOCK_LENGTH]
	, uint8_t dest[BASE64_INPUT_BLOCK_LENGTH])
{
	uint8_t	sextets[BASE64_OUTPUT_BLOCK_LENGTH];
	size_t	input_block_length;

	input_block_length = base64_algo_decode_get_block_to_decode_length(
		to_decode);
	if (base64_algo_decode_characters_to_indexes(to_decode) != E_SUCCESS)
		return (-1);
	base64_algo_decode_compute_sextets(to_decode, input_block_length, sextets);
	base64_algo_decode_sextets_to_octets(sextets, dest);
	return (input_block_length - 1);
}
