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


execute_bash()
{
	(./minishell < ${1}) > ${LOG} 2> ${LOG_2}
	YOUR_RET=($?)
	(bash < ${1}) > ${RESULT} 2> ${RESULT_2}
	OUR_RET=($?)
	if [ $OUR_RET -ne $YOUR_RET ]; then
		printf "\nSTDIN--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[31m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\r\n\033[31mError:\t\t\033[0m\033[37;1m ./minishell ${1}    <=>   bash ${1}\033[0m\n\n"
		printf "bash return: %d | minishell return: %d\n\n" $OUR_RET $YOUR_RET
		quit
	elif !(diff  ${LOG} ${RESULT}) then
		printf "\nSTDIN--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[31m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\r\n\033[31mError STDOUT:\t\t\033[0m\033[37;1m ./minishell ${1}    <=>   bash ${1}\033[0m\n\n"
		diff  ${LOG} ${RESULT}
		quit
	else
		printf "\n\033[32mSTDIN\033[0m--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[32m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\n\033[32mSuccess:\t\033[37;1m ./minishell ${1}    <=>   bash ${1}\033[0m\n\n"
		printf "\nSTDERR--------------------------------------------------------------\n"
		diff  ${RESULT_2} ${LOG_2}
		printf "\n--------------------------------------------------------------------\n"
	fi
}

execute_bash_empty()
{
	(env -i ./minishell ${1}) > ${LOG} 2> ${LOG_2}
	YOUR_RET=($?)
	(env -i bash < ${1}) > ${RESULT} 2> ${RESULT_2}
	OUR_RET=($?)
	if [ $OUR_RET -ne $YOUR_RET ]; then
		printf "\nSTDIN--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[31m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\r\n\033[31mError:\t\t\033[0m\033[37;1m env -i ./minishell ${1}     <=>   env -i bash ${1}\033[0m\n\n"
		printf "env -i bash return: %d | env -i ./minishell return: %d\n\n" $OUR_RET $YOUR_RET
		quit
	elif !(diff  ${LOG} ${RESULT}) then
		printf "\nSTDIN--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[31m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\r\n\033[31mError STDOUT:\t\t\033[0m\033[37;1m env -i ./minishell ${1}     <=>   env -i bash ${1}\033[0m\n\n"
		diff  ${LOG} ${RESULT}
		quit
	else
		printf "\n\033[32mSTDIN\033[0m--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[32m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\n\033[32mSuccess:\t\033[37;1m env -i ./minishell ${1}     <=>   env -i bash ${1}\033[0m\n\n"
		printf "\nSTDERR--------------------------------------------------------------\n"
		diff  ${RESULT_2} ${LOG_2}
		printf "\n--------------------------------------------------------------------\n"
	fi
}

execute_csh()
{
	(./minishell ${1}) > ${LOG} 2> ${LOG_2}
	YOUR_RET=($?)
	(csh < ${1}) > ${RESULT} 2> ${RESULT_2}
	OUR_RET=($?)
	if !(diff  ${LOG} ${RESULT}) then
		printf "\nSTDIN--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[31m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\r\n\033[31mError STDOUT:\t\t\033[0m\033[37;1m ./minishell ${1}    <=>   csh ${1}\033[0m\n\n"
		diff  ${LOG} ${RESULT}
		quit
	else
		printf "\n\033[32mSTDIN\033[0m--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[32m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\n\033[32mSuccess:\t\033[37;1m ./minishell ${1}   <=>   csh ${1}\033[0m\n\n"
		printf "\nSTDERR--------------------------------------------------------------\n"
		diff  ${RESULT_2} ${LOG_2}
		printf "\n--------------------------------------------------------------------\n"
	fi
}


execute_csh_empty()
{
	(env -i ./minishell ${1}) > ${LOG} 2> ${LOG_2}
	YOUR_RET=($?)
	(env -i csh ${1}) > ${RESULT} 2> ${RESULT_2}
	OUR_RET=($?)
	if !(diff  ${LOG} ${RESULT}) then
		printf "\nSTDIN--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[31m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\r\n\033[31mError STDOUT:\t\t\033[0m\033[37;1m env -i ./minishell ${1}   <=>   env -i csh ${1}\033[0m\n\n"
		diff  ${LOG} ${RESULT}
		quit
	else
		printf "\n\033[32mSTDIN\033[0m--------------------------------------------------------------\n"
		while read line 
		do 
		echo -e "\033[32m$line\033[0m" 
		done <  ${1}
		printf "\033[0m-----------------------------------------------------------------\033[0m\n"
		printf "\n\033[32mSuccess:\t\033[37;1m env -i ./minishell  ${1}   <=>   env -i csh ${1}\033[0m\n\n"
		printf "\nSTDERR--------------------------------------------------------------\n"
		diff  ${RESULT_2} ${LOG_2}
		printf "\n--------------------------------------------------------------------\n"
	fi
}



rm -rf leaks


for filename in $(ls tests_csh/); do
    echo Test tests_csh/${filename}
	execute_csh tests_csh/${filename}
	echo Test leaks tests_csh/${filename}
	valgrind --track-origins=yes --show-leak-kinds=all --track-fds=yes 		\
				--show-reachable=no --leak-check=full env -i ./minishell tests_csh/${filename} 2>> leaks
    echo Test env -i tests_csh/${filename}
	execute_csh_empty tests_csh/${filename}
	echo Test env -i leaks tests_csh/${filename}
	valgrind --track-origins=yes --show-leak-kinds=all --track-fds=yes 		\
				--show-reachable=no --leak-check=full env -i ./minishell tests_csh/${filename} 2>> leaks
done



for filename in $(ls tests_sh/); do
    echo Test tests_sh/${filename}
	execute_bash tests_sh/${filename}
	echo Test leaks tests_sh/${filename}
	valgrind --track-origins=yes --show-leak-kinds=all --track-fds=yes 		\
				--show-reachable=no --leak-check=full ./minishell tests_sh/${filename} 2>> leaks
    echo Test env -i tests_sh/${filename}
	execute_bash_empty tests_sh/${filename}
	echo Test env -i leaks tests_sh/${filename}
	valgrind --track-origins=yes --show-leak-kinds=all --track-fds=yes 		\
				--show-reachable=no --leak-check=full env -i ./minishell tests_sh/${filename} 2>> leaks
done

rm -rf ${TMP_DIR} ${TMP_DIR_LOG}
exit 0