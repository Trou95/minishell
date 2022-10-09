/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interpreter.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:44:57 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 09:45:09 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INTERPRETER_H
# define MINISHELL_INTERPRETER_H

# include <stdio.h>
# include "../parser/utils/parser_utils.h"
# include "../../Libft/libft.h"

char	**interpreter_array_format(char **arr, t_vars *g_data);

char	*ft_check_quote(const char *str, t_vars *g_data);
char	*ft_double_quote(const char *str, int *end_index, t_vars *g_data);
char	*ft_quote(const char *str, int *end_index);
char	*ft_format(const char *str, int	*env_len, t_vars *g_data);
char	*interpreter_qouete(const char *str, char qt, int *idx, t_vars *g_data);

char 	*ft_retvalue(int value);

char	*ft_envjoin(char *dst, char *src);
int		ft_get_env_len(const char *str);
int		ft_get_env(const char *str, char **env);
int		ft_is_valid_env(const char *str);

#endif