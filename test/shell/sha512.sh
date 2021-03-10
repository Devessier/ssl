#!/usr/bin/env bash

testSHA512InvalidArgument() {
	command="./ft_ssl sha512 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: sha512: illegal option -- invalid_argument$
usage: ft_ssl sha512 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA512InvalidDoubleDash() {
	command="./ft_ssl sha512 --a"
	read -d '' usage << EOF
ft_ssl: sha512: illegal option -- -a$
usage: ft_ssl sha512 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA512BasicStringHashing() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512 -s "${string_to_hash}")
	official_result='SHA512 ("1") = 4dff4ea340f0a823f15d3f4f01ab62eae0e5da579ccb851f8db9dfe84c58b2b37b89903a740e1ee172da793a6e79d560e5f7f9bd058a12a280433ed6fa46510a'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512BasicStringHashingInQuietMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512 -q -s "${string_to_hash}")
	official_result='4dff4ea340f0a823f15d3f4f01ab62eae0e5da579ccb851f8db9dfe84c58b2b37b89903a740e1ee172da793a6e79d560e5f7f9bd058a12a280433ed6fa46510a'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512BasicStringHashingInReverseMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512 -r -s "${string_to_hash}")
	official_result='4dff4ea340f0a823f15d3f4f01ab62eae0e5da579ccb851f8db9dfe84c58b2b37b89903a740e1ee172da793a6e79d560e5f7f9bd058a12a280433ed6fa46510a "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512BasicStringHashingInReverseAndQuietModes() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512 -r -q -s "${string_to_hash}")
	official_result='4dff4ea340f0a823f15d3f4f01ab62eae0e5da579ccb851f8db9dfe84c58b2b37b89903a740e1ee172da793a6e79d560e5f7f9bd058a12a280433ed6fa46510a'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'

	hash_result=$(./ft_ssl sha512 -s "${string_to_hash}")
	official_result='SHA512 ("Salut à vous tous ! Ceci est un super projet ssl !") = 8da0b114435b6ea8b48a6f2cdcb17b2efbceb2ab177f6cd78df15e3fbf1f7996cef2db5fa01b93ac0867d23546cbaa9bca1ae13e68bf907e95dbe15c34643d0c'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512ReadsBigFileFromStdin() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/19603/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $TMP_DIR/pdf.pdf | ./ft_ssl sha512 -p | cat -e > $HASHING_RESULT_FILE
	cat << EOF > $OFFICIAL_RESULT_FILE
$(cat -e $TMP_DIR/pdf.pdf)
391d1816e10022df1e5fe644dc8cd82b6e7dc9c7eab925a630da3a91bfcdec01e23a0f889b74d2667b9be23abb34df4b59636312beb0a5bdd2789a1f352155ac$
EOF

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

# 42 subject tests

testSHA512ReadsFromStdinWhenNoArgumentsAreProvided() {
	string_to_hash='pickle rick'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512)
	official_result='1d1a1921d70a90b7c984a4a36370aaf7d699faa516a00c6f828439a99b8c949733cde9e2c578b39f084440363532e85bd5705b7141077c4661655d700092e6c4'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512ReadsFromStdinAndPrintInputText() {
	string_to_hash='Do not pity the dead, Harry.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512 -p | cat -e)
	read -d '' official_result << EOF
Do not pity the dead, Harry.$
cbbb5025780ff59bde8a3e7fd493c61da587441c4f16225e43d3f5c4770656ae3e8701c2e4c63d06cd2fbde36702008cfc0c109dbea88f4798401bab4be1e3fb$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512ReadsFromStdinAndDoesNotTakeIntoAccountQuietAndReverseModes() {
	string_to_hash='Pity the living.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512 -q -r)
	official_result='eeff6ebf504b8c42ac83af9ca87096703946dd42fc93015c37bfe801c3539307e7659fa3ded3c982e38d26b960c153b8de6bd3b55dfdf488eda506a2e01b8b96'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512ReadsFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha512 $TMP_FILE)
	official_result="SHA512 ($TMP_FILE) = 4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512ReadsFromFileInReverseMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha512 -r $TMP_FILE)
	official_result="4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d $TMP_FILE"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512MediumStringHashing2() {
	string_to_hash="pity those that aren't following baerista on spotify."

	hash_result=$(./ft_ssl sha512 -s "$string_to_hash")
	official_result="SHA512 (\"pity those that aren't following baerista on spotify.\") = c06dd99415006509229a70c60d41b28b6138217551d195fbd6135ac8afcec0d7e050f2470c855ba1b9155cd7b7c74b27f7f15cee9f16912613f5b88ec109ff1f"

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512ReadsFromStdinThenFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl sha512 -p $TMP_FILE | cat -e)
	read -d '' official_result << EOF
be sure to handle edge cases carefully$
352cdbc6c6f4fc47032f36786f182ba58a42bcf35a06b39a646b59e640b98335eb07a9bbd03e9859a8eaae2f148a1b528a7c236db0d9599d41e05f16ddf235ab$
SHA512 ($TMP_FILE) = 4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512DoesNotReadStdinIfCanReadFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "some of this will not make sense at first" | ./ft_ssl sha512 $TMP_FILE | cat -e)
	official_result="SHA512 ($TMP_FILE) = 4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d$"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512ReadsFromStdinEvenIfFileProvidedIfInPrintMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "but eventually you will understand" | ./ft_ssl sha512 -p -r $TMP_FILE | cat -e)
	read -d '' official_result << EOF
but eventually you will understand$
a7ffee36cc2fc95f6880b7e9c137eadee67cf07c0e89b7d2acfafa9d3a95ba2c5cffc7e2cb068fe51c37edaf569d4397564863c0ca95484bae0959ed31b541d4$
4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d $TMP_FILE$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512ReadsFromStdinEvenIfFileProvidedIfInPrintModeAndHashesString() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "GL HF let's go" | ./ft_ssl sha512 -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
GL HF let's go$
ace7a0d8f8d5907452c4d4b5a9d5699de6e75b0263dafe5e0a7b30ef50e4be20a108db78ec2218434bd913ffdff26fa1c3d0e2a15d08fc1d113315e506de8a39$
SHA512 ("foo") = f7fbba6e0636f890e56fbbf3283e524c6fa3204ae298382d624741d0dc6638326e282c41be5e4254d8820772c5518a2c5a8c0c7f7eda19594a7eb539453e1ed7$
SHA512 ($TMP_FILE) = 4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512ConsidersArgumentsAfterFirstFileAsFiles() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "one more thing" | ./ft_ssl sha512 -r -p -s "foo" $TMP_FILE -s "bar" 2>&1 | cat -e)
	read -d '' official_result << EOF
one more thing$
a440177c36cfca4ca61f4e380fe69eec8a5fbbac34d21e0e1c403cfa68c980055b0bf0c7cdc8d2e7154f3959dbcfa86ec4e8503f7b3bf420ce29936947f61924$
f7fbba6e0636f890e56fbbf3283e524c6fa3204ae298382d624741d0dc6638326e282c41be5e4254d8820772c5518a2c5a8c0c7f7eda19594a7eb539453e1ed7 "foo"$
4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d $TMP_FILE$
ft_ssl: sha512: -s: No such file or directory$
ft_ssl: sha512: bar: No such file or directory$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512AllParametersWorkProperlyWhenUsedTogether() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "just to be extra clear" | ./ft_ssl sha512 -r -q -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
just to be extra clear$
b865829a32dcfb9c72ef467ea2619d1aa26ae89d053a9f866e843ac4b46f47f59f9b867afdb6574319b16b7ee7ec8961dda61ce486afc4a4e9f32ad1335774cb$
f7fbba6e0636f890e56fbbf3283e524c6fa3204ae298382d624741d0dc6638326e282c41be5e4254d8820772c5518a2c5a8c0c7f7eda19594a7eb539453e1ed7$
4652fbb98fb2706702dcce8d7a0c24c0443e43c0e9845ad700ffbd9c1ce0b0b712fc362efdbd2ff0756b857c4a79eb089ca3698cd0ec5dafdd9b6602d922616d$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

. ./vendor/shunit2/shunit2
