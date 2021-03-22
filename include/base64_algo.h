/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:21:15 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/22 13:21:44 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_ALGO_H
# define BASE64_ALGO_H
# include "base64.h"

int8_t	base64_decode_encoded_character(uint8_t character);
size_t	base64_algo_decode_get_block_to_decode_length(
	uint8_t to_decode[BASE64_OUTPUT_BLOCK_LENGTH]);

#endif
