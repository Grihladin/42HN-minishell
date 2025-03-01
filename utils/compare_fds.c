/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:14:58 by psenko            #+#    #+#             */
/*   Updated: 2025/03/01 12:18:29 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare_fds(int fd1, int fd2)
{
	struct stat		stat1;
	struct stat		stat2;

	fstat(fd1, &stat1);
	fstat(fd2, &stat2);
	return ((stat1.st_dev == stat2.st_dev)
		&& (stat1.st_ino == stat2.st_ino));
}
