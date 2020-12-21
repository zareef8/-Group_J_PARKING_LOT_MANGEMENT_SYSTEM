#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details here the Operator will be asked to enter the admin password.
* If that matches the password then it will be AUTHENTICATED.
*
* @param[in] Admin Password from user
*
* @return it will return true if the Password matches otherwise it returns false
*/



bool validateAdmin()
{
	printf("Enter Admin Password : ");
	scanf("%s", &admin.password);
	if (strcmp(pass, admin.password) == 0)
	{
		return true;
	}
	else
		return false;
}
