#!/usr/bin/env sh

testMD5InvalidArgument() {
	command="./ft_ssl md5 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: md5: illegal option -- invalid_argument$
usage: ft_ssl md5 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testMD5InvalidDoubleDash() {
	command="./ft_ssl md5 --a"
	read -d '' usage << EOF
ft_ssl: md5: illegal option -- -a$
usage: ft_ssl md5 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testMD5BasicStringHashing() {
	string_to_hash="1"

	hash_result="$(./ft_ssl md5 -s $string_to_hash)"
	official_result='MD5 ("1") = c4ca4238a0b923820dcc509a6f75849b'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5BasicStringHashingInQuietMode() {
	string_to_hash="1"

	hash_result="$(./ft_ssl md5 -q -s $string_to_hash)"
	official_result='c4ca4238a0b923820dcc509a6f75849b'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5BasicStringHashingInReverseMode() {
	string_to_hash="1"

	hash_result="$(./ft_ssl md5 -r -s $string_to_hash)"
	official_result='c4ca4238a0b923820dcc509a6f75849b "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5BasicStringHashingInReverseAndQuietModes() {
	string_to_hash="1"

	hash_result="$(./ft_ssl md5 -r -q -s $string_to_hash)"
	official_result='c4ca4238a0b923820dcc509a6f75849b'

	assertEquals "${official_result}" "${hash_result}"
}

. ./vendor/shunit2/shunit2
