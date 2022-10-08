#include "minishell.h"

void	build_add_redirection(char *arg, char *type, t_redirection **redir, int *check_redir)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_calloc(sizeof(char) * ft_strlen(arg) + 1,sizeof(char));
	tmp = ft_str_clearquotes(arg, ptr);
	ft_lstadd_back_redir(redir, new_s_redirection(type, tmp));
	free(arg);
	*check_redir = 0;
}

char	*build_typer(char *str, int *index, int *check_redir)
{
	char	*tmp;

	if (*check_redir == 1)
		printf("SYNTAX ERROR redir çift redir falan\n");
	tmp = ft_substr(str, *index, is_redir(&(str[*index])));
	ft_memset(&str[*index], ' ', ft_strlen(tmp));
	*index += ft_strlen(tmp);
	*check_redir = 1;
	return (tmp);
}

char	*build_qouete_join(char *str, int *index)
{
	int		i;
	char	*tmp;
	char	*n_str;
	int		len;

	i = 0;
	len = 0;
	n_str = malloc(sizeof(char));
	*n_str = '\0';
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			len = parser_quote_endidx(&str[i + 1], str[i]);
			tmp = ft_substr(&str[i + 1], 0, len);
			n_str = ft_free_strjoin(n_str, tmp);
			i += len + 2;
			free(tmp);
		}
		else
			break ;
	}
	*index += i;
	return (n_str);
}

//leak
char	*build_qoete(char *str, int *index)
{
	char	*tmp;
	char	*n_str;
	char	quote;

	n_str = ft_calloc(1,sizeof(char));
	while (str[*index])
	{
		if (str[*index] == '"' || str[*index] == '\'')
		{
			quote = str[*index];
			tmp = build_qouete_join(&str[*index], index);
			n_str = ft_free_strjoin(n_str, tmp);
			n_str = ft_strappend(n_str, quote);
			free(tmp);
		}
		else if (str[*index] != ' ' && !is_redir(&str[*index]))
		{
			n_str = ft_free_strjoin(n_str, ft_substr(str, *index, 1));
			n_str = ft_strappend(n_str, '"');
			(*index)++;
		}
		else
			break ;
	}
	return (n_str);
	//return ft_strappend(n_str, '"'); silince 25 oluyo
}

char	*build_arger(char *str, int *index, int *check_redir)
{
	int		start_index;
	char	*tmp;

	start_index = *index;
	if (str[*index] == '"' || str[*index] == '\'')
	{
		//tmp = ft_substr(str, *index, ft_get_chrindex(&str[*index + 1], str[*index]) + 2);
		tmp = build_qoete(str, index);
		ft_memset(&str[start_index], ' ', *index - start_index);
		(*index)--;
	}
	else
	{
		while (str[*index] && (str[*index] != ' ' && !is_redir(&str[*index])))
			(*index)++;
		tmp = ft_substr(str, start_index, *index - start_index);
		ft_memset(&str[start_index], ' ', ft_strlen(tmp));
		(*index)--;
	}
	//*index += ft_strlen(tmp);
	*check_redir = 2;
	return (tmp);
}

//type'ın tırkan içinde olma durumu
void	build_redirection(t_redirection **redir, char	**cmd)
{
	int		check_redir;
	char	*type;
	char	*arg;
	int		idx;
	t_redirection *tmp_redir; //silinecek sadece ekrana basmak için kullanılıyor

	idx = -1;
	check_redir = 0;
	type = arg = NULL;
	printf("-------\n");
	printf("%s\n",*cmd);
	printf("-------\n");
	while (++idx < (int)ft_strlen(cmd[0]))
	{
		if (check_redir == 0 && (cmd[0][idx] == '"' || cmd[0][idx] == '\''))
		{
			idx += ft_strchr(&(cmd[0][idx + 1]), cmd[0][idx]) - &(cmd[0][idx]);

		}
		if(is_redir(&(cmd[0][idx])))
			type = build_typer(cmd[0], &idx, &check_redir);
		if (check_redir == 1 && cmd[0][idx] != ' ' && !is_redir(&cmd[0][idx]))
		{
			arg = build_arger(cmd[0],&idx,&check_redir);
		}
		if (check_redir == 2)
		{
			build_add_redirection(arg,type,redir,&check_redir);
			type = NULL;
			//free(arg);
			arg = NULL;
			//check_redir = 0;
		}
		//printf("ASAMA REDİR:_%s_\n",cmd[0]);
	}
	if (!*redir)
		*redir = NULL;
	else
	{
		//printf("REDIR_REDIR_REDIR\n");
		tmp_redir = *redir;
		while (tmp_redir)
		{
			//printf("redir type: _%s_ arg: _%s_\n", tmp_redir->redir, tmp_redir->args);
			tmp_redir = tmp_redir->next;
		}

	}
}

//echo > "a"''"b"c "asdadad" adsadas2