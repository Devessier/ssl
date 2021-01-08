/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:53 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 00:58:31 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA384_ALGO_H
# define SHA384_ALGO_H
# include "ssl.h"
# include "reader.h"

void		sha384_algo(t_context *ctx, t_reader *reader);

#endif
