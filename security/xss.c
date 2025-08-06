

#include "../inc/secure.h"
#include "../inc/http.h"

char *patterns[] = {
    "script",
    "onerror",
    "onload",
    "javascript:",
    "data:text/html",
    "img",
    "iframe",
    "svg",
    "object",
    "embed",
    NULL
};


int check_xss(struct request req)
{
	size_t		i = 0;
	size_t		j;
	
	j = 0;
	while(patterns[j]!=NULL && req.query_string)
	{
		if(strstr(req.query_string , patterns[j]))
			return 0;
		j++;
	}

	while(req.data[i].key && req.data[i].value)
	{
		j = 0;

		while(patterns[j]!=NULL)
		{
			printf("%s\n" , patterns[j]);
			if(strstr(req.data[i].value , patterns[j]))
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}
