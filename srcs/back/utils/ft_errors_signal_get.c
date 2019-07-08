/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_signal_get.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 01:54:31 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 22:41:48 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const char	*ft_errors_signal_get_2(int signal)
{
	if (signal == SIGSEGV)
		return ("Segmentation fault: 11");
	else if (signal == SIGSYS)
		return ("Bad system call: 12");
	else if (signal == SIGPIPE)
		return ("Broken pipe: 13");
	else if (signal == SIGALRM)
		return ("Alarm clock: 14");
	else if (signal == SIGTERM)
		return ("Terminated: 15");
	else if (signal == SIGXCPU)
		return ("Cputime limit exceeded: 24");
	else if (signal == SIGXFSZ)
		return ("Filesize limit exceeded: 25");
	else if (signal == SIGVTALRM)
		return ("Virtual timer expired: 26");
	else if (signal == SIGPROF)
		return ("Profiling timer expired: 27");
	else if (signal == SIGUSR1)
		return ("User defined signal 1: 30");
	else if (signal == SIGUSR2)
		return ("User defined signal 2: 31");
	return ("Running");
}

const char			*ft_errors_signal_get(int signal)
{
	if (signal == SIGHUP)
		return ("Hangup: 1");
	else if (signal == SIGINT)
		return ("");
	else if (signal == SIGQUIT)
		return ("Quit: 3");
	else if (signal == SIGILL)
		return ("Illegal instruction: 4");
	else if (signal == SIGTRAP)
		return ("Trace/BPT trap: 5");
	else if (signal == SIGABRT)
		return ("Abort trap: 6");
	else if (signal == SIGFPE)
		return ("Floating point exception: 8");
	else if (signal == SIGKILL)
		return ("Killed: 9");
	else if (signal == SIGBUS)
		return ("Bus error: 10");
	return (ft_errors_signal_get_2(signal));
}

const char			*ft_errors_stop_get(int sig)
{
	if (sig == SIGTTOU)
		return ("Stopped (SIGTTOU)");
	else if (sig == SIGTSTP)
		return ("Stopped (SIGTSTP)");
	else if (sig == SIGSTOP)
		return ("Stopped (SIGSTOP)");
	else if (sig == SIGTTIN)
		return ("Stopped (SIGTTIN)");
	return ("Stopped");
}
