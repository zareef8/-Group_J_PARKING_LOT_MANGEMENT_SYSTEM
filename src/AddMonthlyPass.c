#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This function will Add a Monthly pass if the Provided data Found in the record
*
* @param[in] Name of The driver
* @param[in] License Plate number
*
* @return it will return 0 if the Montly pass is not Activated otherwise it will return 1
*/

int AddMonthlyPass()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		char key[20]; char key1[20];
		printf("Enter Customer Name : "); scanf("%s", &key);
		printf("Enter License Plate : "); scanf("%s", &key1);
		bool found = false; bool yes = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.name, key) == 0 && strcmp(ptr->c.licensePlate, key1) == 0)
			{
				found = true;
				printf("Data found.\n");
				printf("Want to Purchase Monthly Pass for 100 $ ? (Y / N)\n");
				char opt; fflush(stdin);
				scanf("%c", &opt);
				if (opt == 'y' || opt == 'Y')
				{
					yes = true; break;
				}
				else
				{
					yes = false; break;
				}
			}
			ptr = ptr->next;
		}
		if (found == false)
		{
			printf("Error ! Data not found.\n");

			return 0;
		}
		else if (found == true && yes == true)
		{
			ptr = head;
			while (ptr != NULL)
			{
				if (strcmp(ptr->c.name, key) == 0 && strcmp(ptr->c.licensePlate, key1) == 0)
				{
					strcpy(ptr->c.montlyPass, "Yes");
				}
				ptr = ptr->next;
			}
			printf("Monthly Pass Activated.\n");

			return 1;
		}
	}
}
