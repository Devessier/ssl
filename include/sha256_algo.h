/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:34:55 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 15:36:41 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_ALGO_H
# define SHA256_ALGO_H
# include "ssl.h"
# include "reader.h"

void	sha256_algo(t_context *ctx, t_reader *reader);

#endif
