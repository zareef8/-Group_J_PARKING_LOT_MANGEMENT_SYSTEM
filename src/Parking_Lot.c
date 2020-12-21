#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#define hour 0.167
#define Capacity 100

#include <termios.h>
#include <unistd.h>

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}


char pass[] = "111";
struct Admin
{
	char password[20];
}admin;

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


struct Customer
{
	char name[20];
	char licensePlate[10];
	char status[10];
	char storeEntry[30];
	char storeExit[30];
	char montlyPass[5];
	char blacListed[5];
	time_t entryTime;
	time_t exitTime;
	double price;
	double totalTime;
	int yearDay;
}customer;


struct node {
	struct Customer c;
	struct node *next;
};

struct node *head = NULL;


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


int printAll()
{
	struct node *ptr = head;
	int count = 0;
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (ptr != NULL)
	{
		count++;
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
			ptr->c.blacListed, ptr->c.price);
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		ptr = ptr->next;
	}
	if (count !=0)
	{
		return 1;
	}
	if (count == 0)
	{
		printf("No Vehicles exist in database.\n");
		return 0;
	}
}


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


int DepartureOFVehicle()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		char key[20];
		printf("Enter License Plate to Search: "); scanf("%s", &key);
		bool found = false;
		bool hasMonthlyPass = false;
		bool alreadydeparted = false;
		bool isparked = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				found = true;
				if (strcmp(ptr->c.status, "Departed") == 0)
				{
					alreadydeparted = true;
					if (strcmp(ptr->c.montlyPass, "Yes") == 0)
					{
						hasMonthlyPass = true;
					}
				}
				if (strcmp(ptr->c.status, "Parked") == 0)
				{
					isparked = true;
					if (strcmp(ptr->c.montlyPass, "Yes") == 0)
					{
						hasMonthlyPass = true;
					}
					break;
				}
			}
			ptr = ptr->next;
		}
		if (found == false)
		{
			printf("Error ! Vehicle not found.\n");

			return 0;
		}
		if (alreadydeparted == true && isparked == false)
		{
			printf("Error ! Vehicle already departed.\n");
		}
		if (alreadydeparted == false && isparked == true)
		{
			if (hasMonthlyPass == true)
			{
				printf("This User has a Mothly Pass.\n");
				time(&ptr->c.exitTime);
				strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
				int len = strlen(ptr->c.storeExit);
				ptr->c.storeExit[len - 1] = '\0';
				double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
				seconds = seconds / 60;//3600 for hours
				ptr->c.totalTime = seconds;
				printf("Total Time %.2f Minutes.\n", seconds);
				ptr->c.price = 0.0;
				printf("Total Price (Monthly Pass Active): %.2f \n", ptr->c.price);
				strcpy(ptr->c.status, "Departed");
				printf("Vehicle Departed Successfully.\n");
			}
			else if (hasMonthlyPass == false)
			{
				printf("This User has Simple membership.\n");
				time(&ptr->c.exitTime);
				strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
				int len = strlen(ptr->c.storeExit);
				ptr->c.storeExit[len - 1] = '\0';
				double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
				seconds = seconds / 60;//3600 for hours
				ptr->c.totalTime = seconds;
				printf("Total Time %.2f Minutes.\n", seconds);
				ptr->c.price = seconds * hour;
				printf("Please pay %.2f $ before leaving.\n", ptr->c.price);
				strcpy(ptr->c.status, "Departed");
				printf("Vehicle Departed Successfully.\n");
			}

			return 1;
		}
	}
}



int closingParkingLot()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		bool found = false;
		bool hasMonthlyPass = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.status, "Parked") == 0)
			{
				found = true;
				if (strcmp(ptr->c.montlyPass, "Yes") == 0)
				{
					time(&ptr->c.exitTime);
					strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
					int len = strlen(ptr->c.storeExit);
					ptr->c.storeExit[len - 1] = '\0';
					double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
					seconds = seconds / 60;//3600 for hours
					ptr->c.totalTime = seconds;
					ptr->c.price = 0.0;
					strcpy(ptr->c.status, "Departed");
				}
				else
				{
					time(&ptr->c.exitTime);
					strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
					int len = strlen(ptr->c.storeExit);
					ptr->c.storeExit[len - 1] = '\0';
					double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
					seconds = seconds / 60;//3600 for hours
					ptr->c.totalTime = seconds;
					ptr->c.price = seconds * hour;
					strcpy(ptr->c.status, "Departed");
				}
			}
			ptr = ptr->next;

		}
		if (found == false)
		{
			printf("There were no parked vehicles.Closing Parking Lot.\n");

            return 0;
		}
		else
		{
			printf("All Vehicles departed from Parking lot.\n");
		}
	}
}


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
				printf("Want to Purchase Monthly Pass for 100 $ ? (Yes-1 / No-2)\n");
				int opt; fflush(stdin);
				printf("Please Press 1 or 2 "); scanf("%d", &opt);
				if (opt == 1)
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


int AddToBlackList()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		char key[20];
		printf("Enter License Plate : "); scanf("%s", &key);
		bool found = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				found = true;
				printf("Data found.\n");
				strcpy(ptr->c.blacListed, "Yes");
			}
			ptr = ptr->next;
		}
		if (found == false)
		{
			printf("Error ! Data not found.\n");

			return 0;
		}
		else

			printf("Vehicle Black Listed.\n");
			return 1;
	}
}



int RemoveFromBlackList()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		char key[20];
		printf("Enter License Plate : "); scanf("%s", &key);
		bool found = false;
		bool bfound = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				printf("Data found.\n"); found = true;
				if (strcmp(ptr->c.blacListed, "No") == 0)
				{
					printf("Error ! This vehicle is not Black Listed.\n"); bfound = true; break;
				}
				else
				{
					strcpy(ptr->c.blacListed, "No");
				}
			}
			ptr = ptr->next;
		}
		if (found == false)
		{
			printf("Error ! Data not found.\n");
			return 0;
		}
		else if (bfound == false)
			printf("Vehicle Removed from Black List.\n");
			return 1;
	}
}


int printAllBlacklisted()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		struct node *ptr = head;
		int count = 0;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.blacListed, "Yes") == 0)
			{
				count++;
				printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
					ptr->c.blacListed, ptr->c.price);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}
			ptr = ptr->next;
		}
		if (count == 0)
		{
			printf("No Black listed Vehicles exist in database.\n");
		}
		return 1;
	}
}


int printAllParked()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		struct node *ptr = head;
		int count = 0;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.status, "Parked") == 0)
			{
				count++;
				printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
					ptr->c.blacListed, ptr->c.price);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}
			ptr = ptr->next;
		}
		if (count == 0)
		{
			printf("No Parked Vehicles exist in database.\n");
		}

		return 1;
	}
}


int SearchByLicensePlate()
{
    int data_found=0;
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}

	else
	{
		char key[20];
		printf("Enter License Plate to search: "); scanf("%s", &key);
		bool found = false;
		struct node *ptr = head;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				found = true;
				printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
					ptr->c.blacListed, ptr->c.price);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				data_found++;

			}
			ptr = ptr->next;
		}
		if(data_found>0)
        {
            return 1;
        }

		if (found == false)
		{
			printf("Vehicles not Found in database.\n");
			return 0;
		}
	}
}


int loadFromFile()
{
	FILE *fptr1;
	if ((fptr1 = fopen("data.txt", "r")) == NULL)
	{
		printf("Error! File not opened.");
		return 0;
		exit(1);
	}
	char line[40]; double prc = 0; double ttl = 0; bool found = false; int len;
	while (fgets(line, sizeof(line), fptr1))
	{
		struct node *link = (struct node*) malloc(sizeof(struct node));
		len = strlen(line);
		line[len - 1] = '\0';
		strcpy(link->c.name, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.licensePlate, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.status, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.storeEntry, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.storeExit, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.montlyPass, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.blacListed, line);
		char *eptr;
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; link->c.price = strtod(line, &eptr);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; link->c.totalTime = strtod(line, &eptr);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; link->c.yearDay = atoi(line);
		link->next = head;
		head = link;
	}
	fclose(fptr1);
	printf("Data Loaded from File Successfully.\n");
	return 1;
}


int saveIntoFile()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		FILE*fptr;
		fptr = fopen("data.txt", "w");
		struct node *ptr = head;
		while (ptr != NULL)
		{
			fprintf(fptr, "%s\n", ptr->c.name);
			fprintf(fptr, "%s\n", ptr->c.licensePlate);
			fprintf(fptr, "%s\n", ptr->c.status);
			fprintf(fptr, "%s\n", ptr->c.storeEntry);
			fprintf(fptr, "%s\n", ptr->c.storeExit);
			fprintf(fptr, "%s\n", ptr->c.montlyPass);
			fprintf(fptr, "%s\n", ptr->c.blacListed);
			fprintf(fptr, "%.2lf\n", ptr->c.price);
			fprintf(fptr, "%.2lf\n", ptr->c.totalTime);
			fprintf(fptr, "%d\n", ptr->c.yearDay);

			ptr = ptr->next;
		}
		fclose(fptr);

		return 1;
	}
}


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


int past30Days()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		time_t rawtime;
		struct tm *info;
		time(&rawtime);
		info = localtime(&rawtime);
		int key = info->tm_yday;
		int count = 0;
		struct node*ptr;
		ptr = head;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while (ptr != NULL)
		{
			if ((key - ptr->c.yearDay) <= 30)
			{
				count++;
				printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
					ptr->c.blacListed, ptr->c.price);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}
			ptr = ptr->next;
		}
		if (count == 0)
		{
			printf("No Vehicles came in past 30 Days.\n");
		}

		return 1;
	}
}



int main()
{
	loadFromFile(); getchar();
	int initialOption = 0;
	int adminOption = 0;
	int customerOption = 0;
	FILE *fptr;
	fptr = fopen("data.txt", "a");
	fclose(fptr);
	while (initialOption != 3)
	{
		//system("cls");
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
					getchar();
					break;
				}
				case 2:
				{
					printAll();
					getchar();
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





