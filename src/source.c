#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @brief This function is to display list of options Or Features for This Parking Lot Management System

* @details This will Show Admin, Customer menu and Exit Menu
* User must need to use Exit function to Exit the program.
* Admin Menu Has 6 Options and Some of them Contains Sub options
* Customer Menu has 4 Options
*
* @param[in] User will be asked to Enter the option they want to choose
*
* @return it will return 0 after running the program successfully
*/

int main()
{
	loadFromFile(); getch();
	int initialOption = 0;
	int adminOption = 0;
	int customerOption = 0;
	FILE *fptr;
	fptr = fopen("data.txt", "a");
	fclose(fptr);
	while (initialOption != 3)
	{
		system("cls");
		initial_menu();
		scanf("%d", &initialOption);
		switch (initialOption)
		{
		case 1:
		{
			if (validateAdmin() == true)
			{
				Admin_menu();
				scanf("%d", &adminOption);
				switch (adminOption)
				{
				case 1:
				{
					printAllParked();
					getch();
					break;
				}
				case 2:
				{
					printAll();
					getch();
					break;
				}
				case 3:
				{
					SearchByLicensePlate();
					getch();
					break;
				}
				case 4:
				{
					FILE*ptr;
					ptr = fopen("data.txt", "w");
					fclose(ptr);
					struct node *temp;
					while (head != NULL)
					{
						temp = head;
						head = head->next;
						free(temp);
					}
					printf("All content of File Deleted.\n");
					getch();
					break;
				}
				case 5:
				{
					int choice = 0;
					Blacklist_menu();
					scanf("%d", &choice);
					switch (choice)
					{
					case 1:
					{
						AddToBlackList();
						getch();
						break;
					}
					case 2:
					{
						RemoveFromBlackList();
						getch();
						break;
					}
					case 3:
					{
						printAllBlacklisted();
						getch();
						break;
					}
					default:
					{
						printf("Error!! Please select correct option.\n"); getch();
						break;
					}
					}
					break;
				}
				case 6:
				{
					int choice = 0;
					Reports_menu();
					scanf("%d", &choice);
					switch (choice)
					{
					case 1:
					{
						sd();
						getch();
						break;
					}
					case 2:
					{
						printf("Average Paring Time : %.2lf\n", averageParkTime());
						getch();
						break;
					}
					case 3:
					{
						past30Days();
						getch();
						break;
					}
					default:
					{
						printf("Error!! Please select correct option.\n"); getch();
						break;
					}
					}
					break;
				}
				default:
				{
					printf("Error!! Please select correct option.\n"); getch();
					break;
				}
				}
			}
			else
			{
				printf("Wrong Password.\n"); getch();
			}
			break;
		}
		case 2:
		{
			Customer_menu();
			scanf("%d", &customerOption);
			switch (customerOption)
			{
			case 1:
			{
				ArrivalOfVehicle();
				getch();
				break;
			}
			case 2:
			{
				DepartureOFVehicle();
				getch();
				break;
			}
			case 3:
			{
				printf("Total Space Available: %d\n", Capacity - TotalParked());
				getch();
				break;
			}
			case 4:
			{
				AddMonthlyPass();
				getch();
				break;
			}
			default:
			{
				printf("Error!! Please select correct option.\n"); getch();
				break;
			}
			}
			break;
		}
		case 3:
		{
			printf("Exiting System.\n");
			closingParkingLot();
			printAll();
			saveIntoFile(); getch();
			exit(1);
			break;
		}
		default:
		{
			printf("Error!! Please select correct option.\n");
			break;
		}
		}
	}
	return 0;
}
