/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 22:59:02 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/25 00:17:28 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDIANNESS_H
# define ENDIANNESS_H
# include <unistd.h>

uint64_t	endianness_swap64(uint64_t number);

#endif
