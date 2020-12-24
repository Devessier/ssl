/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:25:06 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 13:08:33 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ssl.h"
#include "hexa.h"

void		md5_hash_print(uint8_t hash[MD5_HASH_SIZE])
{
	size_t	index;

	index = 0;
	while (index < MD5_HASH_SIZE)
		print_hexa_num(STDOUT_FILENO, hash[index++]);
}
