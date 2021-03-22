/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_algo_decode_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:20:07 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:21:01 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

int8_t	base64_decode_encoded_character(uint8_t character)
{
	size_t			index;

	index = 0;
	while (index < BASE64_DICTIONARY_LENGTH)
	{
		if (g_base64_dictionary[index] == character)
			return (index);
		index++;
	}
	return (-1);
}

size_t	base64_algo_decode_get_block_to_decode_length(
	uint8_t to_decode[BASE64_OUTPUT_BLOCK_LENGTH])
{
	if (to_decode[2] == '=')
		return (2);
	if (to_decode[3] == '=')
		return (3);
	return (4);
}
