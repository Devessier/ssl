/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:27:36 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/24 01:08:26 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "libft.h"
#include "hexa.h"

static const char	g_hexa_lookup_table[] = "0123456789abcdef";

static int8_t	hexa_char_to_integer(char c)
{
	size_t		index;

	index = 0;
	while (index < sizeof(g_hexa_lookup_table) - 1)
	{
		if (g_hexa_lookup_table[index] == ft_tolower(c))
			return (index);
		index++;
	}
	return (-1);
}

t_hexa_to_uint64_result		hexa_to_uint64(const char *str, size_t length)
{
	const size_t	max_str_length = sizeof(uint64_t) * 2;
	uint64_t		number;
	int8_t			char_integer_value;
	size_t			index;

	if (ft_strlen(str) > max_str_length)
		return ((t_hexa_to_uint64_result) {
			.error = E_FAILURE,
		});
	number = 0;
	index = 0;
	while (index < length)
	{
		char_integer_value = hexa_char_to_integer(str[index]);
		if (char_integer_value == -1)
			return ((t_hexa_to_uint64_result) {
				.error = E_FAILURE,
			});
		number *= 16;
		number += char_integer_value;
		index++;
	}
	return ((t_hexa_to_uint64_result) {
		.number = number,
		.error = E_SUCCESS,
	});
}

void			print_uint64_to_hexa(int fd, uint64_t num)
{
	char			buffer[HEXA_UINT64_BLOCKS] = { 0 };
	size_t			index;
	char			hexa_character;

	index = 0;
	while (index < HEXA_UINT64_BLOCKS)
	{
		hexa_character = ft_toupper(g_hexa_lookup_table[(num >> (4 * index)) & 0xf]);
		buffer[index] = hexa_character;
		index++;
	}
	write(fd, buffer, sizeof(buffer));
}

void			print_hexa_num(int fd, uint8_t num)
{
	char		buffer[2];
	ssize_t		hex_length;

	hex_length = 2;
	while (--hex_length >= 0)
	{
		buffer[hex_length] = g_hexa_lookup_table[num & 0xf];
		num >>= 4;
	}
	write(fd, buffer, 2);
}

void			print_hexa_buffer(int fd, uint8_t *buffer, size_t length)
{
	size_t	index;

	index = 0;
	while (index < length)
	{
		print_hexa_num(fd, buffer[index]);
		index++;
	}
}
