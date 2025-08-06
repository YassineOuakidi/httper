#ifndef SECURE_H
#define SECURE_H

#include "../libft/libft.h"
#include <stdlib.h>

struct request;

int secure(struct request req);

int check_chars(struct request req);
int check_xss(struct request req);
//int check_login_bypass(req);
//int check_header(req);
//int check_sqli(req);
//int check_session_cookie(req);
//int check_command_injection(req);
//int check_template_injection(req);
//int check_directory_traversal(req);


#endif
