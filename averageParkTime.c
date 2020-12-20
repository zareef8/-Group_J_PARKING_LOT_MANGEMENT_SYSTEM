#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details This function will give the average parking time for all Vehicles.
* It counts the time from the data file and from real time entry
*
* @param[in] there is not Input for the function
*
* @return it will return the average park time, However if the database is empty it return 0
*/


double averageParkTime()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		int count = 0; double total = 0;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			total = total + ptr->c.totalTime;
			count++;
			ptr = ptr->next;
		}
		return (total / count);
	}
}
