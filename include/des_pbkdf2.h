/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pbkdf2.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 01:34:33 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/25 00:08:27 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_PBKDF_H
# define DES_PBKDF_H
# include "ssl.h"

uint64_t	des_pbkdf2(
	char *password
	, size_t password_length
	, uint64_t salt
	, size_t iter);

#endif
