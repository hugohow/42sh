#!/bin/bash

TMP_DIR=~/tmp_minishell
TMP_DIR_LOG=~/tmp_minishell_log
LOG=${TMP_DIR_LOG}/log
RESULT=${TMP_DIR_LOG}/result
LOG_2=${TMP_DIR_LOG}/log_2
RESULT_2=${TMP_DIR_LOG}/result_2


mkdir ${TMP_DIR}
mkdir ${TMP_DIR_LOG}

rm -rf leaks

for filename in $(ls tests/tests_sh); do
	valgrind --track-origins=yes --show-leak-kinds=all --track-fds=yes 		\
				--show-reachable=no --leak-check=full ./minishell tests/tests_sh/${filename} 2>> leaks
done

rm -rf ${TMP_DIR} ${TMP_DIR_LOG}
exit 0