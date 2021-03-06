/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:34:55 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 00:58:43 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_ALGO_H
# define SHA224_ALGO_H
# include "ssl.h"
# include "reader.h"

void		sha224_algo(t_context *ctx, t_reader *reader);

#endif
