/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_args.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:30:18 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 16:00:16 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "catch.hpp"
extern "C" {
	#include "args.h"
}

TEST_CASE( "Parses a boolean flag and sets its value to true" ) {
	const int			argc = 1;
	const char			*argv[] = {
		"-p",
		0
	};
	bool				p_flag = false;
	const t_arg			args[] = {
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"p",
			.value = &p_flag,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0,
			NULL
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);

	REQUIRE( p_flag == true );
}

TEST_CASE( "Parses an empty input and does not argument value to true" ) {
	const int			argc = 0;
	const char			*argv[] = { 0 };
	bool				p_flag = false;
	const t_arg			args[] = {
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"p",
			.value = &p_flag,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0,
			NULL
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);

	REQUIRE( p_flag == false );
}

TEST_CASE( "Parses several boolean flags and sets their values" ) {
	const int			argc = 3;
	const char			*argv[] = {
		"-a",
		"-b",
		"-c",
		0
	};
	bool				flag1 = false;
	bool				flag2 = false;
	bool				flag3 = false;
	const t_arg			args[] = {
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"a",
			.value = &flag1,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"b",
			.value = &flag2,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"c",
			.value = &flag3,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0,
			NULL
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);

	REQUIRE( flag1 == true );
	REQUIRE( flag2 == true );
	REQUIRE( flag3 == true );
}

TEST_CASE( "Parses several boolean flags with some missing and sets their values" ) {
	const int			argc = 2;
	const char			*argv[] = {
		"-a",
		"-c",
		0
	};
	bool				flag1 = false;
	bool				flag2 = false;
	bool				flag3 = false;
	const t_arg			args[] = {
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"a",
			.value = &flag1,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"b",
			.value = &flag2,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"c",
			.value = &flag3,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0,
			NULL
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);

	REQUIRE( flag1 == true );
	REQUIRE( flag2 == false );
	REQUIRE( flag3 == true );
}

TEST_CASE( "Parses a string flag and sets its value to true" ) {
	const int			argc = 2;
	const char			*argv[] = {
		"-p",
		"test",
		0
	};
	char				*p_flag = NULL;
	const t_arg			args[] = {
		{
			.type = ARG_STRING,
			.name = (char *)"p",
			.value = &p_flag,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0,
			NULL
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);

	REQUIRE( strcmp(p_flag, "test") == 0 );
}

TEST_CASE( "Parses several string flags with some missing and sets their values" ) {
	const int			argc = 4;
	const char			*argv[] = {
		"-a",
		"test1",
		"-c",
		"test2",
		0
	};
	char				*flag1 = NULL;
	char				*flag2 = NULL;
	char				*flag3 = NULL;
	const t_arg			args[] = {
		{
			.type = ARG_STRING,
			.name = (char *)"a",
			.value = &flag1,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = (char *)"b",
			.value = &flag2,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = (char *)"c",
			.value = &flag3,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0,
			NULL
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);

	REQUIRE( strcmp(flag1, "test1") == 0 );
	REQUIRE( flag2 == NULL );
	REQUIRE( strcmp(flag3, "test2") == 0 );
}

TEST_CASE( "Parses boolean and string flags and sets their values" ) {
	const int			argc = 5;
	const char			*argv[] = {
		"-a",
		"test1",
		"-c",
		"test2",
		"-w",
		0
	};
	char				*flag1 = NULL;
	char				*flag2 = NULL;
	char				*flag3 = NULL;
	bool				flag4 = false;
	bool				flag5 = false;
	const t_arg			args[] = {
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"w",
			.value = &flag4,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = (char *)"a",
			.value = &flag1,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = (char *)"b",
			.value = &flag2,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_BOOLEAN,
			.name = (char *)"x",
			.value = &flag5,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = (char *)"c",
			.value = &flag3,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0,
			NULL
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);

	REQUIRE( strcmp(flag1, "test1") == 0 );
	REQUIRE( flag2 == NULL );
	REQUIRE( strcmp(flag3, "test2") == 0 );
	REQUIRE( flag4 == true );
	REQUIRE( flag5 == false );
}
