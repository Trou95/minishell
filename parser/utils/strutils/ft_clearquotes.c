#include "../parser_utils.h"

char	*ft_str_clearquotes(const char *str, char *ptr)
{
	t_redir_var	v;
	char		c;

	ft_memset(&v, 0, sizeof(t_redir_var));
	while (str[v.idx])
	{
		if (str[v.idx] == '"' || str[v.idx] == '\'' && \
			(v.idx == 0 || (v.idx > 0 && str[v.idx - 1] != '\\')))
		{
			c = str[v.idx];
			while (str[++v.idx] && str[v.idx] != c)
			{
				if (str[v.idx] == '\\')
					v.idx++;
				ptr[v.n_idx++] = str[v.idx];
			}
		}
		else
		{
			if (str[v.idx] == '\\')
				v.idx++;
			ptr[v.n_idx++] = str[v.idx++];
		}
	}
	return (ptr);
}
