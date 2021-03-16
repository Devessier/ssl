#!/usr/bin/env bash

# testMD5InvalidArgument() {
# 	command="./ft_ssl md5 -invalid_argument"
# 	read -d '' usage << EOF
# ft_ssl: md5: illegal option -- invalid_argument$
# usage: ft_ssl md5 [-p] [-q] [-r] [-s string] [files ...]$
# EOF

# 	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

# 	eval "$command 2> /dev/null"
# 	assertEquals 'invalid exit status' 1 $?
# }

. ./vendor/shunit2/shunit2
