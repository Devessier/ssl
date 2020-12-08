/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reader.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:41:37 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/08 03:42:13 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "catch.hpp"
extern "C" {
	#include "reader.h"
}

SCENARIO("Power off tests", "[power_button]")
{
	GIVEN("the power is off")
	{
		WHEN("nothing happens")
		{
			THEN("the power is still off")
			{
				REQUIRE(lol() == 1);
			}
		}

		WHEN("nothing happens")
		{
			THEN("the power is still off")
			{
				REQUIRE(lol() == 0);
			}
		}
	}
}
