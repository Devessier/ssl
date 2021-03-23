#!/usr/bin/env bash

testDesInvalidArgument() {
	command="./ft_ssl des -invalid_argument"
	read -d '' usage << EOF
ft_ssl: des: illegal option -- invalid_argument$
usage: ft_ssl des [-ade] [-print-key-iv] [-i in_file] [-o out_file] [-k key] [-p password] [-s salt] [-v iv]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

. ./vendor/shunit2/shunit2
