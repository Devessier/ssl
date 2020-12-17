/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:27:36 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 20:02:49 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

void		print_hexa_num(int fd, uint8_t num)
{
	const char	hexa_lookup_table[] = "0123456789abcdef";
	char		buffer[2] = { 0 };
	ssize_t		hex_length;

	hex_length = 2;
	while (--hex_length >= 0)
	{
		buffer[hex_length] = hexa_lookup_table[num & 0xf];
		num >>= 4;
	}
	write(fd, buffer, 2);
}
