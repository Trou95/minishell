#include "../parser_utils.h"

char	*ft_str_clearquotes(const char *str, char *ptr)
{
	t_redir_var	v;
	char		c;

	ft_memset(&v, 0, sizeof(t_redir_var));
	while (str[v.idx])
	{
		if (str[v.idx] == '"' || str[v.idx] == '\'')
		{
			c = str[v.idx];
			v.k_idx = ft_get_chrindex(&str[v.idx + 1],str[v.idx]) + 1;
			if(str[v.k_idx])
				if(ft_strnstr(&str[v.idx]," ",v.k_idx))
				{
					ft_memcpy(&ptr[v.n_idx],&str[v.idx],v.k_idx + 1);
					v.n_idx += v.k_idx + 1;
					v.idx += v.k_idx + 1;
				}
			else
				while (str[++v.idx] && str[v.idx] != c)
					ptr[v.n_idx++] = str[v.idx];
		}
		else
			ptr[v.n_idx++] = str[v.idx++];
	}
	return (ptr);
}
