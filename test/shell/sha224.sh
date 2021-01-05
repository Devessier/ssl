#!/usr/bin/env bash

testSHA224InvalidArgument() {
	command="./ft_ssl sha224 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: sha224: illegal option -- invalid_argument$
usage: ft_ssl sha224 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA224InvalidDoubleDash() {
	command="./ft_ssl sha224 --a"
	read -d '' usage << EOF
ft_ssl: sha224: illegal option -- -a$
usage: ft_ssl sha224 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA224BasicStringHashing() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha224 -s "${string_to_hash}")
	official_result='SHA224 ("1") = e25388fde8290dc286a6164fa2d97e551b53498dcbf7bc378eb1f178'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224BasicStringHashingInQuietMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha224 -q -s "${string_to_hash}")
	official_result='e25388fde8290dc286a6164fa2d97e551b53498dcbf7bc378eb1f178'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224BasicStringHashingInReverseMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha224 -r -s "${string_to_hash}")
	official_result='e25388fde8290dc286a6164fa2d97e551b53498dcbf7bc378eb1f178 "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224BasicStringHashingInReverseAndQuietModes() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha224 -r -q -s "${string_to_hash}")
	official_result='e25388fde8290dc286a6164fa2d97e551b53498dcbf7bc378eb1f178'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'

	hash_result=$(./ft_ssl sha224 -s "${string_to_hash}")
	official_result='SHA224 ("Salut à vous tous ! Ceci est un super projet ssl !") = 1cd28da61ac7be592e9d35996f9b4aa1d321fa53a74f3043eea58ce7'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224ReadsBigFileFromStdin() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/13242/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $TMP_DIR/pdf.pdf | ./ft_ssl sha224 -p | cat -e > $HASHING_RESULT_FILE
	cat << EOF > $OFFICIAL_RESULT_FILE
$(cat -e $TMP_DIR/pdf.pdf)
480283ad32aa586717154c45baeaa758e00342153c27ab199071789c$
EOF

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

# 42 subject tests

testSHA224ReadsFromStdinWhenNoArgumentsAreProvided() {
	string_to_hash='pickle rick'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha224)
	official_result='e4529dbc55d6e02a6a135896dd0a50435fcd1a4240a376e3c7805de3'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224ReadsFromStdinAndPrintInputText() {
	string_to_hash='Do not pity the dead, Harry.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha224 -p | cat -e)
	read -d '' official_result << EOF
Do not pity the dead, Harry.$
7bba6e0dea06e9a4e5ccef4778f92a6e313dd04ef6404d5275dcea07$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224ReadsFromStdinAndDoesNotTakeIntoAccountQuietAndReverseModes() {
	string_to_hash='Pity the living.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha224 -q -r)
	official_result='fa52b99972cdcfbf27c3968fa06b87249f4bfe29e53bc6988ae09c88'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224ReadsFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha224 $TMP_FILE)
	official_result="SHA224 ($TMP_FILE) = 4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA224ReadsFromFileInReverseMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha224 -r $TMP_FILE)
	official_result="4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf $TMP_FILE"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA224MediumStringHashing2() {
	string_to_hash="pity those that aren't following baerista on spotify."

	hash_result=$(./ft_ssl sha224 -s "$string_to_hash")
	official_result="SHA224 (\"pity those that aren't following baerista on spotify.\") = d5e856b036047b934a393487121d5981a2cfb0fa6b97d0e66f2b42cf"

	assertEquals "${official_result}" "${hash_result}"
}

testSHA224ReadsFromStdinThenFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl sha224 -p $TMP_FILE | cat -e)
	read -d '' official_result << EOF
be sure to handle edge cases carefully$
79b7fe4a7c8ac818cc9f136ec1f13012eed0f5888b1895f9c77b1235$
SHA224 ($TMP_FILE) = 4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA224DoesNotReadStdinIfCanReadFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "some of this will not make sense at first" | ./ft_ssl sha224 $TMP_FILE | cat -e)
	official_result="SHA224 ($TMP_FILE) = 4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf$"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA224ReadsFromStdinEvenIfFileProvidedIfInPrintMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "but eventually you will understand" | ./ft_ssl sha224 -p -r $TMP_FILE | cat -e)
	read -d '' official_result << EOF
but eventually you will understand$
612ba055b3238f7b04113778d77884cba7e362369516f78e5c1497c0$
4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf $TMP_FILE$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA224ReadsFromStdinEvenIfFileProvidedIfInPrintModeAndHashesString() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "GL HF let's go" | ./ft_ssl sha224 -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
GL HF let's go$
65b713885260f441ca866252487e8aa66094f6c20a7b985685b5d829$
SHA224 ("foo") = 0808f64e60d58979fcb676c96ec938270dea42445aeefcd3a4e6f8db$
SHA224 ($TMP_FILE) = 4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA224ConsidersArgumentsAfterFirstFileAsFiles() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "one more thing" | ./ft_ssl sha224 -r -p -s "foo" $TMP_FILE -s "bar" 2>&1 | cat -e)
	read -d '' official_result << EOF
one more thing$
1efb20ffc3829a7455c089403bf312d538a8e2e5fb9270dc9fe92314$
0808f64e60d58979fcb676c96ec938270dea42445aeefcd3a4e6f8db "foo"$
4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf $TMP_FILE$
ft_ssl: sha224: -s: No such file or directory$
ft_ssl: sha224: bar: No such file or directory$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA224AllParametersWorkProperlyWhenUsedTogether() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "just to be extra clear" | ./ft_ssl sha224 -r -q -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
just to be extra clear$
00e44d133c4c26ca5aa52342d5238301641ce99d2850cf6fd3bc9918$
0808f64e60d58979fcb676c96ec938270dea42445aeefcd3a4e6f8db$
4071b20c13752233693d28cc51a4056772aa745d8032b0c3bcb82faf$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

. ./vendor/shunit2/shunit2
