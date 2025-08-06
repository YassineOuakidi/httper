
#include "../inc/secure.h"
#include "../inc/http.h"


int check_chars(struct request req)
{
	size_t		i = 0;
	printf("%s\n" ,  req.url);
	while(req.url && req.url[i]!= '\0')
	{
		if(strchr("<>;\"'$@" , req.url[i]))
			return 0;
		i++;
	}
	i = 0;
	if(req.query_string)
		while(req.query_string && req.query_string[i])
		{
			if(strchr("<>;\"'$@" , req.query_string[i]))
				return 0;
			i++;
		}

	i = 0;

	if(req.content_len==0)
		return 1;

	while(req.data[i].key && req.data[i].value)
	{
		size_t		j = 0;
		while(req.data[i].value[j])
		{
			if(strchr("<>;\"'$@" , req.data[i].value[j]))
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}


int secure(struct request req)
{
	return check_chars(req) && check_xss(req);	
}

