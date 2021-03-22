#!/usr/bin/env bash

testBinaryExists() {
	assertTrue 'ft_ssl bin does not exist or can not be executed' "[ -x ./ft_ssl ]"
}

testSslRepl() {
	command="md5 -s \"this string's great!\""
	read -d '' replResult << EOF
ft_ssl_>_MD5_("this_string's_great!")_=_26dbe6f8d9b07adfb168fc192d2ba256$
ft_ssl_>_
EOF

	assertEquals "${replResult}" "$(echo ${command} | ./ft_ssl | cat -e | tr -s '[:blank:]' '_')"
}

testSslReplMultipleCommands() {
	TMP_FILE=$(mktemp)
	cat > $TMP_FILE << EOF
md5 -s "this string's great"
sha512256 -r -s 'hey everybody!'
EOF

	read -d '' replResult << EOF
ft_ssl_>_MD5_("this_string's_great")_=_c1e5460e0be455573b6c61d397f2f7cc$
ft_ssl_>_9dc867cfeee0c638c00d009b62c25686c322b409c7b86b4d12edece5098fcecb_"hey_everybody!"$
ft_ssl_>_
EOF

	assertEquals "${replResult}" "$(cat ${TMP_FILE} | ./ft_ssl | cat -e | tr -s '[:blank:]' '_')"

	rm $TMP_FILE
}

testSslReplCanQuit() {
	TMP_FILE=$(mktemp)
	cat > $TMP_FILE << EOF
md5 -s "this string's great"
quit
sha512256 -r -s 'hey everybody!'
EOF

	read -d '' replResult << EOF
ft_ssl_>_MD5_("this_string's_great")_=_c1e5460e0be455573b6c61d397f2f7cc$
ft_ssl_>_
EOF

	assertEquals "${replResult}" "$(cat ${TMP_FILE} | ./ft_ssl | cat -e | tr -s '[:blank:]' '_')"

	rm $TMP_FILE
}

testSslReplWithoutEmptyParameters() {
	TMP_FILE=$(mktemp)
	cat > $TMP_FILE << EOF
md5 -s lol

md5 -s lol
EOF

	read -d '' replResult << EOF
ft_ssl_>_MD5_("lol")_=_9cdfb439c7876e703e307864c9167a15$
ft_ssl_>_ft_ssl_>_MD5_("lol")_=_9cdfb439c7876e703e307864c9167a15$
ft_ssl_>_
EOF

	assertEquals "${replResult}" "$(cat ${TMP_FILE} | ./ft_ssl 2>&1 | cat -e | tr -s '[:blank:]' '_')"

	rm $TMP_FILE
}

testSslReplConsidersEmptyQuotesAsAString() {
	TMP_FILE=$(mktemp)
	cat > $TMP_FILE << EOF
md5 -s ""
md5 -s ''
EOF

	read -d '' replResult << EOF
ft_ssl_>_MD5_("")_=_d41d8cd98f00b204e9800998ecf8427e$
ft_ssl_>_MD5_("")_=_d41d8cd98f00b204e9800998ecf8427e$
ft_ssl_>_
EOF

	assertEquals "${replResult}" "$(cat ${TMP_FILE} | ./ft_ssl 2>&1 | cat -e | tr -s '[:blank:]' '_')"

	rm $TMP_FILE
}

testSslReplHandleSyntaxErrorKindly() {
	TMP_FILE=$(mktemp)
	cat > $TMP_FILE << EOF
md5 -s "
md5 -s "lol"
EOF

	read -d '' replResult << EOF
ft_ssl_>_ft_ssl:_repl:_syntax_error:_md5_-s_"$
ft_ssl_>_MD5_("lol")_=_9cdfb439c7876e703e307864c9167a15$
ft_ssl_>_
EOF

	assertEquals "${replResult}" "$(cat ${TMP_FILE} | ./ft_ssl 2>&1 | cat -e | tr -s '[:blank:]' '_')"

	rm $TMP_FILE
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
sha224$
sha256$
sha384$
sha512$
sha512224$
sha512256$
$
Cipher commands:$
base64$
EOF

	assertEquals "${usage}" "$(${command} 2>&1 | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 1 $?
}

testSslHelp() {
	TMP_FILE=$(mktemp)
	cat > $TMP_FILE << EOF
help
EOF

	read -d '' usage << EOF
ft_ssl_>_Standard_commands:$
$
Message_Digest_commands:$
md5$
sha224$
sha256$
sha384$
sha512$
sha512224$
sha512256$
$
Cipher_commands:$
base64$
ft_ssl_>_
EOF

	assertEquals "${usage}" "$(cat ${TMP_FILE} | ./ft_ssl 2>&1 | cat -e | tr -s '[:blank:]' '_')"

	rm $TMP_FILE
}

testSslHelpFromRepl() {
	command="./ft_ssl help"
	read -d '' usage << EOF
Standard commands:$
$
Message Digest commands:$
md5$
sha224$
sha256$
sha384$
sha512$
sha512224$
sha512256$
$
Cipher commands:$
base64$
EOF

	assertEquals "${usage}" "$(${command} 2>&1 | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 0 $?
}

. ./vendor/shunit2/shunit2
