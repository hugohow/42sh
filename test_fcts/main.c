#include <stdio.h>
#include <assert.h>
#include "shell.h"

static void print_list(char **list)
{
	int i;

	i = 0;
	while (list[i])
	{
		printf("list[%d] : %s\n", i, list[i]);	
		i++;
	}
}

int main(void)
{
	char **list;
	printf("-------------Test ft_str_separate-------------\n");
	list = ft_str_separate("", '|');
	printf("\033[32mCheck '' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "") == 0);
	assert(list[1] == 0);
	print_list(list);
	list = ft_str_separate("ls | cat -e", '|');
	printf("\033[32mCheck 'ls | cat -e' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], " cat -e") == 0);
	assert(list[2] == 0);
	print_list(list);
	list = ft_str_separate("| cat -e", '|');
	printf("\033[32mCheck '| cat -e' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], " cat -e") == 0);
	assert(list[2] == 0);
	print_list(list);
	list = ft_str_separate("ls |", '|');
	printf("\033[32mCheck 'ls |' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] == 0);
	print_list(list);
	list = ft_str_separate("ls || ls -l", '|');
	printf("\033[32mCheck 'ls || ls -l' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l") == 0);
	assert(list[3] == 0);
	print_list(list);

	list = ft_str_separate("ls ||| ls -l", '|');
	printf("\033[32mCheck 'ls ||| ls -l' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], "") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], " ls -l") == 0);
	assert(list[4] == 0);
	print_list(list);

	list = ft_str_separate("|", '|');
	printf("\033[32mCheck '|' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	print_list(list);


	list = ft_str_separate("|| ls ||", '|');
	printf("\033[32mCheck '|| ls ||' for |\033[00m\n");
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "") == 0);
	assert(list[5] == NULL);
	print_list(list);


	list = ft_str_separate("|| ls ||q|", '|');
	printf("\033[32mCheck '|| ls ||q|' for |\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "q") == 0);
	assert(list[5] != NULL);
	assert(ft_strcmp(list[5], "") == 0);
	assert(list[6] == NULL);




	list = ft_str_separate("ls || ls -l", '$');
	printf("\033[32mCheck 'ls || ls -l' for $\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls || ls -l") == 0);
	assert(list[1] == NULL);


	printf("-------------Test ft_str_separate_str-------------\n");


	list = ft_str_separate_str("||", "||");
	printf("\033[32mCheck '||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);



	list = ft_str_separate_str("ls || ls -l", "||");
	printf("\033[32mCheck 'ls || ls -l' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], " ls -l") == 0);


	list = ft_str_separate_str("ls || ls -l", "||");
	printf("\033[32mCheck 'ls || ls -l' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], " ls -l") == 0);

	list = ft_str_separate_str("ls |||| ls -l", "||");
	printf("\033[32mCheck 'ls |||| ls -l' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l") == 0);
	assert(list[3] == 0);

	list = ft_str_separate_str("ls |||| ls -l |", "||");
	printf("\033[32mCheck 'ls |||| ls -l |' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l |") == 0);
	assert(list[3] == 0);


	list = ft_str_separate_str("ls |||| ls -l ||", "||");
	printf("\033[32mCheck 'ls |||| ls -l ||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] == 0);


	list = ft_str_separate_str("ls |||| ls -l |||", "||");
	printf("\033[32mCheck 'ls |||| ls -l |||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "|") == 0);
	assert(list[4] == 0);



	list = ft_str_separate_str("ls |||| ls -l ||||", "||");
	printf("\033[32mCheck 'ls |||| ls -l ||||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "") == 0);
	assert(list[5] == 0);


	list = ft_str_separate_str("ls |||| ls -l |||||", "||");
	printf("\033[32mCheck 'ls |||| ls -l |||||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "|") == 0);
	assert(list[5] == 0);

	list = ft_str_separate_str("ls |||| ls -l ||||||", "||");
	printf("\033[32mCheck 'ls |||| ls -l ||||||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "") == 0);
	assert(list[5] != NULL);
	assert(ft_strcmp(list[5], "") == 0);
	assert(list[6] == 0);



	list = ft_str_separate_str("ls |||| ls -l ||||||q", "||");
	printf("\033[32mCheck 'ls |||| ls -l ||||||q' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "") == 0);
	assert(list[5] != NULL);
	assert(ft_strcmp(list[5], "q") == 0);
	assert(list[6] == 0);

	list = ft_str_separate_str("ls |||| ls -l ||||||q|", "||");
	printf("\033[32mCheck 'ls |||| ls -l ||||||q|' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "") == 0);
	assert(list[5] != NULL);
	assert(ft_strcmp(list[5], "q|") == 0);
	assert(list[6] == 0);
	assert(list[7] == 0);



	list = ft_str_separate_str("ls |||| ls -l ||||||q||", "||");
	printf("\033[32mCheck 'ls |||| ls -l ||||||q||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "") == 0);
	assert(list[5] != NULL);
	assert(ft_strcmp(list[5], "q") == 0);
	assert(list[6] != NULL);
	assert(ft_strcmp(list[6], "") == 0);
	assert(list[7] == 0);



	list = ft_str_separate_str("| ls |||| ls -l ||||||q||", "||");
	printf("\033[32mCheck 'ls |||| ls -l ||||||q||' for '||'\033[00m\n");
	print_list(list);
	assert(list != NULL);
	assert(list[0] != NULL);
	assert(ft_strcmp(list[0], "| ls ") == 0);
	assert(list[1] != NULL);
	assert(ft_strcmp(list[1], "") == 0);
	assert(list[2] != NULL);
	assert(ft_strcmp(list[2], " ls -l ") == 0);
	assert(list[3] != NULL);
	assert(ft_strcmp(list[3], "") == 0);
	assert(list[4] != NULL);
	assert(ft_strcmp(list[4], "") == 0);
	assert(list[5] != NULL);
	assert(ft_strcmp(list[5], "q") == 0);
	assert(list[6] != NULL);
	assert(ft_strcmp(list[6], "") == 0);
	assert(list[7] == 0);

	return (0);
}