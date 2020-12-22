#!/usr/bin/env sh

testBinaryExists() {
	assertTrue 'ft_ssl bin does not exist or can not be executed' "[ -x ./ft_ssl ]"
}

testSslUsage() {
	command="./ft_ssl"
	read -d '' usage << EOF
usage: ft_ssl command [command opts] [command args]$
EOF

	assertEquals "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 1 $?
}

testSslInvalidCommand() {
	command="./ft_ssl invalid_command"
	read -d '' usage << EOF
ft_ssl: Error: 'invalid_command' is an invalid command.$
$
Standard commands:$
$
Message Digest commands:$
md5$
sha256$
$
Cipher commands:$
EOF

	assertEquals "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 1 $?
}

. ./vendor/shunit2/shunit2
