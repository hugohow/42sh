#!/bin/bash

TMP_DIR=~/tmp_minishell
TMP_DIR_LOG=~/tmp_minishell_log
LOG=${TMP_DIR_LOG}/log
RESULT=${TMP_DIR_LOG}/result
LOG_2=${TMP_DIR_LOG}/log_2
RESULT_2=${TMP_DIR_LOG}/result_2


mkdir ${TMP_DIR}
mkdir ${TMP_DIR_LOG}

quit()
{
	rm -rf ${TMP_DIR} ${TMP_DIR_LOG}
	exit 1
}


execute()
{
	bash ${1} > ${RESULT} 2> ${RESULT_2}
	OUR_RET=($?)
	./minishell ${1} > ${LOG} 2> ${LOG_2}
	YOUR_RET=($?)
	if [ $OUR_RET -ne $YOUR_RET ]; then
		printf "\r\n\033[31mError:\t\t\033[0m\033[37;1m minishell ${1}\033[0m\n\n"
		printf "bash return: %d | minishell return: %d\n\n" $OUR_RET $YOUR_RET
		quit
	elif [ $OUR_RET -ne 0 ] && !(diff  ${LOG_2} ${RESULT_2}); then
		printf "\r\n\033[31mError:\t\t\033[0m\033[37;1m minishell ${1}\033[0m\n\n"
		diff  ${RESULT_2} ${LOG_2}
		quit
	elif !(diff  ${LOG} ${RESULT}) then
		printf "\r\n\033[31mError:\t\t\033[0m\033[37;1m minishell ${1}\033[0m\n\n"
		diff  ${LOG} ${RESULT}
		quit
	else
		printf "\n\033[32mSuccess:\t\033[37;1m minishell ${1}\033[0m\n\n"
	fi
}



for filename in $(ls tests/tests_sh); do
    echo Test tests_sh/${filename}
	execute tests_sh/${filename}
done

rm -rf ${TMP_DIR} ${TMP_DIR_LOG}
exit 0