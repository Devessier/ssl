/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:37:18 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 17:01:15 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA2_H
# define SHA2_H
# include <stdint.h>

extern const uint32_t		g_sha224_sha256_k[];
extern const uint64_t		g_sha384_sha512_k[];

#endif
