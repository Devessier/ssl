/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:37:19 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/24 01:08:43 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEXA_H
# define HEXA_H
# include <stdint.h>
# include <unistd.h>
# include "ssl.h"
# define HEXA_UINT64_BLOCKS 16

typedef struct	s_hexa_to_uint64_result
{
	t_error		error;
	uint64_t	number;
}				t_hexa_to_uint64_result;

t_hexa_to_uint64_result		hexa_to_uint64(const char *str, size_t length);
void						print_uint64_to_hexa(int fd, uint64_t num);
void						print_hexa_num(int fd, uint8_t num);
void						print_hexa_buffer(int fd, uint8_t *buffer, size_t length);


#endif
