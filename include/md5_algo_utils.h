/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 00:00:05 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/23 00:01:15 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_ALGO_UTILS_H
# define MD5_ALGO_UTILS_H
# include <stdint.h>
# include "libft.h"
# include "md5.h"

t_md5_algo_context	md5_init(void);

void				md5_decode_input_le(t_md5_algo_context *ctx
	, uint32_t words[MD5_HASH_SIZE]);

void				md5_encode_output_le(t_md5_algo_context *ctx
	, uint8_t hash[MD5_HASH_SIZE]);

void				add_md5_states(t_md5_states *ref
	, t_md5_states to_add);

void				md5_transform_permute(t_md5_algo_context *ctx
	, t_md5_states *states, size_t index);

#endif
