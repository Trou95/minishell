
int ft_parser_check_quotes(char *str)
{
	int i;
	int count_quote;
	int count_dquate;

	i = 0;
	count_quote = 0;
	count_dquate = 0;
	while(str[i])
	{
		if(str[i] == '"')
		{
			count_dquate++;
			i += ft_parser_check_doublequote(&str[i + 1],&count_dquate, &count_quote);
		}
		else if(str[i] == '\'')
		{
			count_quote++;
			i += ft_parser_check_quote(&str[i + 1], &count_quote);
		}
		i++;
	}
	return (count_dquate % 2 == 0 && count_quote % 2 == 0);
}

int ft_parser_check_doublequote(char *str, int* count_dquote, int* count_quote)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			(*count_dquote)++;
			break;
		}
		else if (str[i] == '\'')
			count_quote += 2;
		i++;
	}
	return ++i;
}

int ft_parser_check_quote(char *str, int *count_quote)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			(*count_quote)++;
			break;
		}
		i++;
	}
	return ++i;
}