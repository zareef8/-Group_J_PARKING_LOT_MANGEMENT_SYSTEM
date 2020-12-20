#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details These are menu for the System Especially for ADMIN and Customer site
*
*
* @param[in] There is no input
*
* @return it will not return anything. It just prints its respective task
*/

void Admin_menu()
{
	printf("1) Display current Vehicles\n");
	printf("2) Display all Drivers profile data\n");
	printf("3) Search A Vehicle By license Plate number\n");
	printf("4) Delete All Records\n");
	printf("5) BlackList\n");
	printf("6) Reports\n");
}
void Blacklist_menu()
{
	printf("1) Black List Vehicle\n");
	printf("2) Remove From Blacklist\n");
	printf("3) Show All Black listed Vehicles\n");
}
void Reports_menu()
{
	printf("1) Standard Deviation\n");
	printf("2) Average park time\n");
	printf("3) Show past 30 Days Records\n");
}
void initial_menu()
{
    printf("+=========================================+\n");
    printf("\n");
    printf(" PARKING LOT MANAGEMENT SYSTEM BY GROUP J \n ");
    printf("\n");
    printf("+=========================================+\n");
    printf("\n");
    printf("\n");


	printf("1) Enter as Admin\n");
	printf("2) Enter as Customer\n");
	printf("3) Exit\n");
}
void Customer_menu()
{
	printf("1) Arrival of a Vehicle\n");
	printf("2) Departure of a Vehicle\n");
	printf("3) Number of space available\n");
	printf("4) Add monthly Pass\n");
}
