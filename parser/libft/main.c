#include <stdio.h>
#include "libft.h"

void f(void *content)
{
	printf("%s",(char *)content);
}

void	array_writer(char **arr)
{
	int i = 0;
	while(arr[i])
	{
		printf("str[%d] => %s\n", i, arr[i]);
		i++;
	}
}

int main()
{
	char **ret;
	char *str = "adasd asd as sadasd           asdasdsadas";

	ret = ft_split(str, ' ');
	array_writer(ret);
}