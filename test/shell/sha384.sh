#!/usr/bin/env bash

testSHA384InvalidArgument() {
	command="./ft_ssl sha384 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: sha384: illegal option -- invalid_argument$
usage: ft_ssl sha384 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA384InvalidDoubleDash() {
	command="./ft_ssl sha384 --a"
	read -d '' usage << EOF
ft_ssl: sha384: illegal option -- -a$
usage: ft_ssl sha384 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA384BasicStringHashing() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha384 -s "${string_to_hash}")
	official_result='SHA384 ("1") = 47f05d367b0c32e438fb63e6cf4a5f35c2aa2f90dc7543f8a41a0f95ce8a40a313ab5cf36134a2068c4c969cb50db776'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384BasicStringHashingInQuietMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha384 -q -s "${string_to_hash}")
	official_result='47f05d367b0c32e438fb63e6cf4a5f35c2aa2f90dc7543f8a41a0f95ce8a40a313ab5cf36134a2068c4c969cb50db776'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384BasicStringHashingInReverseMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha384 -r -s "${string_to_hash}")
	official_result='47f05d367b0c32e438fb63e6cf4a5f35c2aa2f90dc7543f8a41a0f95ce8a40a313ab5cf36134a2068c4c969cb50db776 "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384BasicStringHashingInReverseAndQuietModes() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha384 -r -q -s "${string_to_hash}")
	official_result='47f05d367b0c32e438fb63e6cf4a5f35c2aa2f90dc7543f8a41a0f95ce8a40a313ab5cf36134a2068c4c969cb50db776'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'

	hash_result=$(./ft_ssl sha384 -s "${string_to_hash}")
	official_result='SHA384 ("Salut à vous tous ! Ceci est un super projet ssl !") = a6460a7968ee99b72dac88b59bb8192ad7a0d581f17e3c96575541038253c5bbf409e529f5a9af7a8e324e79aabf640a'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384ReadsBigFileFromStdin() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/19603/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $TMP_DIR/pdf.pdf | ./ft_ssl sha384 -p | cat -e > $HASHING_RESULT_FILE
	cat << EOF > $OFFICIAL_RESULT_FILE
$(cat -e $TMP_DIR/pdf.pdf)
41418cc6593333465d98ae93e1eec774701dd004ee1000eb7ab6403fafa31fd1f047dcd8bcc85eb8fcf8a1bbfa916262$
EOF

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

# 42 subject tests

testSHA384ReadsFromStdinWhenNoArgumentsAreProvided() {
	string_to_hash='pickle rick'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha384)
	official_result='08c3f5ba57482ea5f8478d79800d6647a800f1deaeede53a5a794a151e8ee27670a2c7bd9ad6c83e468801614eac4780'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384ReadsFromStdinAndPrintInputText() {
	string_to_hash='Do not pity the dead, Harry.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha384 -p | cat -e)
	read -d '' official_result << EOF
Do not pity the dead, Harry.$
bda4eacfcc92434bbc8d914234919ef6af9c89916d3e58c4da7cb2d9c316ffab8e506d48ea317c7c044705b2378f9707$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384ReadsFromStdinAndDoesNotTakeIntoAccountQuietAndReverseModes() {
	string_to_hash='Pity the living.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha384 -q -r)
	official_result='7629e1b277eaa39453b47fe9cb4789da57cab72d71a06d312ad9685e7b3e87b0b28a6d184fd5e3c4bb7cc6546baebb01'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384ReadsFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha384 $TMP_FILE)
	official_result="SHA384 ($TMP_FILE) = e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA384ReadsFromFileInReverseMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha384 -r $TMP_FILE)
	official_result="e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b $TMP_FILE"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA384MediumStringHashing2() {
	string_to_hash="pity those that aren't following baerista on spotify."

	hash_result=$(./ft_ssl sha384 -s "$string_to_hash")
	official_result="SHA384 (\"pity those that aren't following baerista on spotify.\") = c49e5969a1679e33a88260dd8d22218d93498c8e096b7b3a49c3a5c25f80a27d765ba7830a507eb8c2949c97941a8db6"

	assertEquals "${official_result}" "${hash_result}"
}

testSHA384ReadsFromStdinThenFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl sha384 -p $TMP_FILE | cat -e)
	read -d '' official_result << EOF
be sure to handle edge cases carefully$
22a9126bd5629476e871bd01f7e3f5389ad6c8190bc0b01866d97a5fe35434f7810334b8f30ea6771e1733939071e33f$
SHA384 ($TMP_FILE) = e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA384DoesNotReadStdinIfCanReadFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "some of this will not make sense at first" | ./ft_ssl sha384 $TMP_FILE | cat -e)
	official_result="SHA384 ($TMP_FILE) = e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b$"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA384ReadsFromStdinEvenIfFileProvidedIfInPrintMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "but eventually you will understand" | ./ft_ssl sha384 -p -r $TMP_FILE | cat -e)
	read -d '' official_result << EOF
but eventually you will understand$
b7f082b516e8ca30aff209862b58dbb6b03adbb9783f2d5fb58c13ccf4afed2ea008cff895cdf106be4d6972832b4d5f$
e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b $TMP_FILE$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA384ReadsFromStdinEvenIfFileProvidedIfInPrintModeAndHashesString() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "GL HF let's go" | ./ft_ssl sha384 -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
GL HF let's go$
449462a4bd60b393f165ef68a10b829b33bef50086d9ef5b0b9dd06f1be50425edcbecac9a231dfaa4ca56a227beaff3$
SHA384 ("foo") = 98c11ffdfdd540676b1a137cb1a22b2a70350c9a44171d6b1180c6be5cbb2ee3f79d532c8a1dd9ef2e8e08e752a3babb$
SHA384 ($TMP_FILE) = e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA384ConsidersArgumentsAfterFirstFileAsFiles() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "one more thing" | ./ft_ssl sha384 -r -p -s "foo" $TMP_FILE -s "bar" 2>&1 | cat -e)
	read -d '' official_result << EOF
one more thing$
52f195be7acd427a06f8a2527156455791454fe7ee026240fe7d75b5a53d28ee90cbfa0a166aad2e7f30c8f653bdd357$
98c11ffdfdd540676b1a137cb1a22b2a70350c9a44171d6b1180c6be5cbb2ee3f79d532c8a1dd9ef2e8e08e752a3babb "foo"$
e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b $TMP_FILE$
ft_ssl: sha384: -s: No such file or directory$
ft_ssl: sha384: bar: No such file or directory$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA384AllParametersWorkProperlyWhenUsedTogether() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "just to be extra clear" | ./ft_ssl sha384 -r -q -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
just to be extra clear$
8ca98065d6aef14c6ac950d95d9998a7f882716094fa19f232c387b35f5e25a03cf934bcd4ba23e8c6286dbad00df4d8$
98c11ffdfdd540676b1a137cb1a22b2a70350c9a44171d6b1180c6be5cbb2ee3f79d532c8a1dd9ef2e8e08e752a3babb$
e696b6db65f90461c7798ecd80d0dc4bf6aad648e576a31c6c5d168aa22d631ddf42d7dc5e860c96944644eca48dec6b$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

. ./vendor/shunit2/shunit2
