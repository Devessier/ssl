/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:27:36 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/16 01:07:16 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

static int	hex_digits(uint8_t num)
{
	int		count;

	if (num == 0)
		return 1;
	count = 0;
	while (num != 0)
	{
		num >>= 4;
		count++;
	}
	return count;
}

void		print_hexa_num(int fd, uint8_t num)
{
	const char	hexa_lookup_table[] = "0123456789abcdef";
	char		buffer[2] = { 0 };
	int			hex_length;

	hex_length = hex_digits(num);
	if (hex_length == 1)
		buffer[0] = '0';
	while (--hex_length >= 0)
	{
		buffer[hex_length] = hexa_lookup_table[num & 0xf];
		num >>= 4;
	}
	write(fd, buffer, 2);
}
