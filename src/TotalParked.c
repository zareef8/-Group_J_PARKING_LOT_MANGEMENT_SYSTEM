#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This function only reads data from data.txt and checked for the "parked" Status.
* then count the parked cars
*
* @param[in] No input is taken here
*
* @return it will return the number of parked vehicles based on Parked status from data.txt
*/



int TotalParked()
{
	int count = 0;
	struct node *ptr = head;
	while (ptr != NULL)
	{
		if (strcmp(ptr->c.status, "Parked") == 0)
			count++;
		ptr = ptr->next;
	}
	return count;
}
