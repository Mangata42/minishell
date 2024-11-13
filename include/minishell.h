/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:50:53 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/13 09:31:05 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdint.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/includes/libft.h"
# include "shell.h"
# include "funny.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"
# include "signal.h"
# include "ast.h"

#endif