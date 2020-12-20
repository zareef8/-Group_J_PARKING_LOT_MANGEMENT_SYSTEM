#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"
/** @details It will count total number of vehicles parked in the system
*
* @param[in] Ther is no input from User for this function
*
* @return it will return the total number of Cars
*/

int TotalVehicles()
{
	int count = 0;
	struct node *ptr = head;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return count;
}
