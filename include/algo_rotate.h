/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_rotate.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:55:48 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/15 19:11:32 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_ROTATE_H
# define ALGO_ROTATE_H
# include <stdint.h>

uint32_t rotl32 (uint32_t value, unsigned int count);
uint32_t rotr32 (uint32_t value, unsigned int count);

#endif
