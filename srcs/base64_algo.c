/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:37:57 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 12:09:47 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "ssl.h"
#include "base64.h"

static const char	g_base64_dictionary[65] = {
	[0] = 'A',
	[1] = 'B',
	[2] = 'C',
	[3] = 'D',
	[4] = 'E',
	[5] = 'F',
	[6] = 'G',
	[7] = 'H',
	[8] = 'I',
	[9] = 'J',
	[10] = 'K',
	[11] = 'L',
	[12] = 'M',
	[13] = 'N',
	[14] = 'O',
	[15] = 'P',
	[16] = 'Q',
	[17] = 'R',
	[18] = 'S',
	[19] = 'T',
	[20] = 'U',
	[21] = 'V',
	[22] = 'W',
	[23] = 'X',
	[24] = 'Y',
	[25] = 'Z',
	[26] = 'a',
	[27] = 'b',
	[28] = 'c',
	[29] = 'd',
	[30] = 'e',
	[31] = 'f',
	[32] = 'g',
	[33] = 'h',
	[34] = 'i',
	[35] = 'j',
	[36] = 'k',
	[37] = 'l',
	[38] = 'm',
	[39] = 'n',
	[40] = 'o',
	[41] = 'p',
	[42] = 'q',
	[43] = 'r',
	[44] = 's',
	[45] = 't',
	[46] = 'u',
	[47] = 'v',
	[48] = 'w',
	[49] = 'x',
	[50] = 'y',
	[51] = 'z',
	[52] = '0',
	[53] = '1',
	[54] = '2',
	[55] = '3',
	[56] = '4',
	[57] = '5',
	[58] = '6',
	[59] = '7',
	[60] = '8',
	[61] = '9',
	[62] = '+',
	[63] = '/',

	[BASE64_PADDING_CHAR] = '=',
};

t_error				base64_algo_encode(uint8_t to_encode[BASE64_INPUT_BLOCK_LENGTH]
	, size_t to_encode_length
	, uint8_t dest[BASE64_OUTPUT_BLOCK_LENGTH])
{
	uint8_t		sextets[BASE64_OUTPUT_BLOCK_LENGTH];
	size_t		index;

	sextets[0] = to_encode[0] >> 2 & 0b111111;
	if (to_encode_length == 1)
		sextets[1] = ((to_encode[0] & 0b11) << 4);
	else
		sextets[1] = ((to_encode[0] & 0b11) << 4) | ((to_encode[1] >> 4) & 0b1111);
	if (to_encode_length == 2)
		sextets[2] = ((to_encode[1] & 0b1111) << 2);
	else if (to_encode_length == 1)
		sextets[2] = BASE64_PADDING_CHAR;
	else
		sextets[2] = ((to_encode[1] & 0b1111) << 2) | ((to_encode[2] >> 6) & 0b11);
	if (to_encode_length == 3)
		sextets[3] = to_encode[2] & 0b111111;
	else
		sextets[3] = BASE64_PADDING_CHAR;
	index = 0;
	while (index < BASE64_OUTPUT_BLOCK_LENGTH)
	{
		dest[index] = g_base64_dictionary[sextets[index]];
		index++;
	}
	return (E_SUCCESS);
}

t_error				base64_algo_decode(uint8_t to_decode[BASE64_OUTPUT_BLOCK_LENGTH]
	, size_t to_decode_length
	, uint8_t dest[BASE64_INPUT_BLOCK_LENGTH])
{
	(void)to_decode;
	(void)to_decode_length;
	(void)dest;

	return (E_SUCCESS);
}
