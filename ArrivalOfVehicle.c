#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This function will Add the given Cars information to the system. User will be asked to provide their name
* and License Plate number.
*
* @param[in] Name of the Driver
* @param[in] License Plate Number
*
* @return it will return 1 If the Vehicle is Added to the system Otherwise it will return 0 when the capacity is full.
*/


int ArrivalOfVehicle()
{
	if (TotalParked() < Capacity)
	{
		struct node *link = (struct node*) malloc(sizeof(struct node));
		printf("Enter Name          :"); scanf("%s", link->c.name);
		printf("Enter Licence Plate :"); scanf("%s", link->c.licensePlate);
		bool alreadyParked = false;
		bool isBlackListed = false;
		bool loyal = false;
		bool hasmp = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(link->c.licensePlate, ptr->c.licensePlate) == 0)
			{
				if (strcmp(ptr->c.blacListed, "Yes") == 0)
				{
					isBlackListed = true;
					break;
				}
				if (strcmp(ptr->c.status, "Departed") != 0)
				{
					alreadyParked = true;
					break;
				}
				if (strcmp(ptr->c.status, "Departed") == 0)
				{
					loyal = true;
				}
				if (strcmp(ptr->c.montlyPass, "Yes") == 0)
				{
					hasmp = true;
				}
			}
			ptr = ptr->next;
		}
		if (alreadyParked == true)
		{
			printf("Error ! Duplicate detected. This vehicle is alreay Parked.\n");
		}
		if (isBlackListed == true)
		{
			printf("Error ! Black Listed Vehicle detected. This vehicle is Blacklisted.\n");
		}
		if (isBlackListed == false && alreadyParked == false)
		{
			if (loyal == true)
			{
				printf("Welcome back loyal Customer.\n");
			}
			if (hasmp == true)
			{
				strcpy(link->c.montlyPass, "Yes");
			}
			else if (hasmp != true)
			{
				strcpy(link->c.montlyPass, "No");
			}
			strcpy(link->c.status, "Parked");
			strcpy(link->c.blacListed, "No");
			time(&link->c.entryTime);
			strcpy(link->c.storeEntry, ctime(&link->c.entryTime));
			int len = strlen(link->c.storeEntry);
			link->c.storeEntry[len - 1] = '\0';
			link->c.price = 0;
			strcpy(link->c.storeExit, "NULL");
			link->c.totalTime = 0;
			////getting year day
			time_t rawtime;
			struct tm *info;
			time(&rawtime);
			info = localtime(&rawtime);
			link->c.yearDay = info->tm_yday;
			///////////////////////////////
			printf("Vehicle Parked Successfully.\n");
			link->next = head;
			head = link;
		}

		return 1;
	}
	else
	{
		printf("Error ! parking already Full.");
		return 0;
	}
}
