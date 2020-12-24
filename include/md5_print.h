/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 13:09:18 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 13:09:37 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_PRINT_H
# define MD5_PRINT_H
# include "ssl.h"

void	md5_hash_print(uint8_t hash[MD5_HASH_SIZE]);

#endif
