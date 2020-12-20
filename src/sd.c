#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details This function shows the standard Deveation for total time
*
* @param[in] No Input from the user side for this function
*
* @return it will return 1 for Showing the Standard Deveation otherwise it will return 0
*/

int sd()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		double mean = averageParkTime();
		int count = TotalVehicles();
		double sum = 0;
		struct node*ptr;
		ptr = head;
		while (ptr != NULL)
		{
			sum = sum + pow((ptr->c.totalTime - mean), 2);
			ptr = ptr->next;
		}
		sum = sum / count;
		printf(" The Standard deviation is : %.2lf\n", sqrt(sum));
		return 1;
	}
}
