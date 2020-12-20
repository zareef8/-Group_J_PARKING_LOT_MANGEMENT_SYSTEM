#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#define hour 5
#define Capacity 100
char pass[] = "111";
struct Admin
{
	char password[20];
}admin;

bool test_validateAdmin()
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


int test_TotalParked()
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


int test_TotalVehicles()
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


int test_printAll()
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


int test_ArrivalOfVehicle()
{
	if (test_TotalParked() < Capacity)
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


int test_DepartureOFVehicle()
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
				printf("Total Time %.2f Hours.\n", seconds);
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
				printf("Total Time %.2f Hours.\n", seconds);
				ptr->c.price = seconds * hour;
				printf("Please pay %.2f $ before leaving.\n", ptr->c.price);
				strcpy(ptr->c.status, "Departed");
				printf("Vehicle Departed Successfully.\n");
			}
			
			return 1;
		}
	}
}



int test_closingParkingLot()
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
			
			return 1;
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


int test_AddMonthlyPass()
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


int test_AddToBlackList()
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



int test_RemoveFromBlackList()
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


int test_printAllBlacklisted()
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


int test_printAllParked()
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


int test_SearchByLicensePlate()
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


int test_loadFromFile()
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


int test_saveIntoFile()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		FILE*fptr;
		fptr = fopen("random_test_save.txt", "w");
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





double test_averageParkTime()
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



int test_sd()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		double mean = test_averageParkTime();
		int count = test_TotalVehicles();
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


int test_past30Days()
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




void test_menu()
{
		printf("\n1. Test ADMIN PASSWORD checker.\n");
    	printf("\n2. Test Total Car Parked Currently.\n");
    	printf("\n3. Test Print all data.\n");
    	printf("\n4. Test Arrival of a vehicle function.\n");
    	printf("\n5. Test Departure of a vehicle function.\n");
    	printf("\n6. Test closing the parking lot function.\n");
    	printf("\n7. Test Add monthly pass function.\n");
    	printf("\n8. Test Add to black list function.\n");
    	printf("\n9. Test Remove from blacklist function.\n");
    	printf("\n10. Test Print all blacklist function.\n");
    	printf("\n11. Test Print all Currently parked function.\n");
    	printf("\n12. Test Search by License Plate function.\n");
    	printf("\n13. Test Load from file function.\n");
    	printf("\n14. Test Save into file function.\n");
    	printf("\n15. Test Average Time parked function.\n");
    	printf("\n16. Test Standard Deviation function.\n");
    	printf("\n17. Test Last 30days Data function.\n");
    	printf("\n18. Test All Menus.\n");
    	printf("\n19 FINISH TESTING \n");
}



int main()
{
    system("color 0B");

    printf("+=================================================+\n");
    printf("\n");
    printf(" TESTING PARKING LOT MANAGEMENT SYSTEM BY GROUP J \n ");
    printf("\n");
    printf("+=================================================+\n");
    printf("\n");
    printf("\n");
    
    
    test_loadFromFile();
    
    printf("\n\nNOTE: **DO NOT REMOVE given [data.txt]  [test_result_data.txt] and [random_test_save.txt] from the same Folder**\n\n");
	printf("\n\nENTER ANY KEY TO CONTINUE TESTING\n \n"); getch();
	
	FILE *fptr;
	fptr = fopen("test_data.txt", "a");
	fclose(fptr);
	
	int count,inp,count_1;
	FILE *test_result = fopen("test_result_data.txt", "a");
	
	
    int test_option=0;
    test_menu();
	
	while(test_option!=19)
	
	{
		
		printf("\n\nPLEASE ENTER YOUR TEST OPTION  :");
    	scanf("%d",&test_option);

	switch(test_option){
        	case 1:
                	printf("\nTesting Admin Password Checker.\n");

			/* Test case 1 - Wrong password */
                	printf("\nEnter an INCORRECT Admin Password(correct password:111)\n");
                    bool result1= test_validateAdmin();
                    if(result1==false){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Invalid password, Expected Output: 0, Output: %d .\n",result1);
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	else{
                    		char t[100];
                    		sprintf(t,"1)FAIL: Input: Invalid password, Expected Output: 0, Output: %d .\n",result1);
                    		printf(t);
                    		fprintf(test_result,t);
                	}

                	/* Test case 2 - Correct password */

                	printf("\nEnter the CORRECT Admin Password(correct password:111)\n");
                    result1= test_validateAdmin();
                	if(result1 == true){
                    		char t[100];
                    		sprintf(t,"2)PASS: Input: correct password, Expected Output: 1, Output: %d .\n",result1);
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: correct password, Expected Output: 1, Output: %d .\n",result1);
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	
                	break;
                	
                	
            case 2: /*Test Case 2 checkes how many car is Parked in the Current System */
                	
					printf("\nTesting total cars parked in the lot.\n");
					test_closingParkingLot();
					test_printAll();
					
                	printf("\nPlease Enter Your Vehicle Information\n\n");
                	test_ArrivalOfVehicle();
                    int result2= test_TotalParked();
                    test_closingParkingLot();
                    
                	if(result2>0){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: 1, Output: %d .\n",result2);
                    		/* Expected output is 1 as the system will depart all cars before taking the new entry */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: 0, Output: %d .\n",result2);
                    		/* For Fail Case Expected output will be 0 as there no Entry will be recorded Even after Providing Cars Info */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	
                	break;
                	
                	
        	case 3: /* This Test Case 3 will Print all Data in the system*/
        		printf("\nTesting Print All Data Function.\n");
        		int result3=test_printAll();
				if(result3 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: 1, Output: %d .\n",result3);
                    		/* Expected output is 1 When It could Print Successfully */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: 0, Output: %d .\n",result3);
                    		/* For Fail Case Expected output will be 0 as there is no entries in the data file */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	
                	break;
				 

            case 4:
               		printf("\nTesting adding vehicles to the parking lot\n");
                	/* general Test case 4 the function returns 1 upon successful parking and 0 otherwise */
                	
                	printf("\nPlease Enter Your Vehicle Information To test this Function\n\n");
                    int result4=test_ArrivalOfVehicle();
                    if(result4 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result4);
                            /*Expected Output is 1 when Vehicled is Added into system*/
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result4);
                    		/* Expected output will be 0 if the Vehicle is not added */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
                	
            case 5:
                    printf("\nTesting Removing of vehicles from the parking lot\n");
                	/* Test case 5 Takes a vehicle then Depart the same vehicle taking info from Client */
                	test_closingParkingLot();
                	
                	printf("\nPlease Enter Your Vehicle Information To test this Function\n\n");
                	test_ArrivalOfVehicle();
                	
                	printf("Now Enter the Same Vehicle License Plate Number to Depart\n");

                	int result5= test_DepartureOFVehicle();
                	
                    if(result5 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result5);
                            /*Expected Output is 1 if Vehicle got Departed*/
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result5);
                    		/* Expected output will be 0 if vehicle is not departed */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
			case 6:
				printf("Testing closing the parking lot function.\n");
				/* Test Case 6 testing if the Closing of the parking lot Function is working Properly it Departs All vehicle for System Maintenance */
				int result6= test_closingParkingLot();
				if(result6 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result6);
                            /*Expected Value is 1 If The function can close the Parking*/
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result6);
                    		/* Expected output will be 0 for Failure of closing the Parking */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
            
            case 7:
            	printf(" Testing add monthly pass function \n ");
            	/*Test Case 7 checks If we can Add a Montly Pass to A Profile who has a Record in Our System*/
            		test_closingParkingLot();
                	
                	printf("\nPlease Enter Your Vehicle Information To test this Function\n\n");
                	test_ArrivalOfVehicle();
                	printf("\nPlease Enter the Same Information To add a Monthly Pass\n\n");
            	int result7= test_AddMonthlyPass();
            	
            	
				if(result7 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result7);
                            /*For Passing the Function the Expected output is 1*/
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result7);
                    		/* Expected output will be 0 if Fails to Activate the Monthly Pass */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
                	
            
            case 8:
            	/* Test Case 8 Checks for if a Vehicle can be Added into BlackList*/
            	
            	printf("Testing Add to Black-List function\n");
            	test_closingParkingLot();
            	
            	printf("\nPlease Enter Your Vehicle Information To test this Function\n\n");
                	test_ArrivalOfVehicle();
                	test_closingParkingLot();
                	printf("\nPlease Enter the Same License Plate Number to Add into Black-List\n\n");
            	
            	int result8= test_AddToBlackList();
				if(result8 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result8);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result8);
                    		
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
            	
            	
            case 9:  	/* Test Case 8 Checks for if a Vehicle can be Removed from BlackList*/
            printf("Testing Remove From BlackList Function  \n");
            
            printf("Enter a Vehicle [i.e 149LM is on Data File Record] from the record to Make It BlackListed\n");
            test_AddToBlackList();
            
            printf("Now Enter the same Vehicle to remove from BlackList \n");
            
            int result9= test_RemoveFromBlackList();
            	
            	
				if(result9 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result9);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result9);
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
                	
            case 10:
            	printf("\nTesting print All Blacklisted Cars Data function\n");
            	int result10= test_printAllBlacklisted();
            	
            	if(result10 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result10);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result10);
                    		/* If the File is not found then it will be Fails and Expected output is 0 for that case*/
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
            	
            
            
            case 11: /* Case 11 Checks if the Print Function Can Print all Currently Parked Vehicles */
            	printf("\nTesting Print All Currently Parked function\n");
            	printf("\n\nIt Shows which Car is Currently Parked [This will Take data from data.txt]\n\n");
            	int result11=test_printAllParked();
            	if(result11 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result11);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result11);
                    		/* Expected output will be 0 if file is not available */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
            	
            	break;
            	
            	
            	
            
            case 12: /* Case 12 Checkes if the Search Function can search a data from File or Real-time Verion*/

            	printf("\nTesting search by License Plate Number function");
            	test_closingParkingLot();
            	printf("\nEnter the Vehicle which you need to search Next\n");
            	test_ArrivalOfVehicle();
            	printf("\nEnter the Same Vehicle Plate Number to Search\n");
            	test_closingParkingLot();
            	int result12=test_SearchByLicensePlate();
            	if(result12 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result12);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result12);
                    		/* Expected output will be 0 if Even after giving the same info Data is lost or not Found */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
                	
            
            case 13:  /*Case 13 Checkes if the data is Loading Properly from the data.txt */
            printf("\nTesting loading from file function \n");
            
            int result13=test_loadFromFile();
            
            if(result13 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result13);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result13);
                    		/* Expected output will be 0 if file is not available */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
                	
                	
            case 14: /* Case 14 Checks if the Save to Function is Saving Real-time Data to a text file Named   [ random_test_save.txt ] */
            	
            	printf("\nTesting save into file function \n");
            	int result14= test_saveIntoFile();
            	
            	if(result14 == 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result14);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else{
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result14);
                    		/* Expected output will be 0 if file is not available */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                
					
                	
            case 15: /* Case 15 checking if the Average Time function can Calculate the Average time from the data.txt */
            	printf("\nTesting Average Time Parked function \n");
            	int result15= test_averageParkTime();
            	
            	if(result15 != 0){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",result15,result15);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		if (result15==0)					   
					   {
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result15);
                    		/* Expected output will be 0 if data.txt Content is deleted*/
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
                	
                	
            case 16: /* Case 16 checking if the Standard Deviation function can Calculate the it from the data.txt */
            	printf("\nTesting Standard deviation function \n");
            	
            	int result16= test_sd();
            	
            	if(result16==1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result16);
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else					   
					   {
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result16);
                    		/* Expected output will be 0 if File Content is deleted */
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                	
            case 17: /*Case 17 Checkes if the past30days Data display function is working properly or not */
            	printf("\nTesting Past 30 Days Vehicle\n\n");
            	printf("\n\n**Some DATA MAY REPEAT for Test Purpose Only!\n\n");
            	int result17= test_past30Days();
            	
            	if(result17== 1){
                    		char t[100];
                    		sprintf(t,"1)PASS: Input: Valid File, Expected Output: %d, Output: %d .\n",1,result17);
                    		 /* Expected Output 1 when the function can read data from the file and display it Properly*/
                            printf(t);
                    		fprintf(test_result,t);
                	}
               		else					   
					   {
                    		char t[100];
                    		sprintf(t,"2)FAIL: Input: Valid file, Expected Output: %d, Output: %d .\n",0,result17);
                    		/* Expected output will be 0 if File not found*/
                    		printf(t);
                    		fprintf(test_result,t);
                	}
                	break;
                
					
            
            case 18:
            	printf("\nTesting All Menu\n");
            	
            	printf("No Test Case for ADMIN Menu, CUSTOMER Menu, BlackList Menu, Reports Menu, Initial Menu\n");
            	/*These menus are just printing words so no test cases */
            	break;
        
        	case 19:
        		printf("\nTest Done! Thank You\n");
        		break;
                	
            
            default:
		{
			printf("Error!! Please select The Correct option.\n");
			break;
		}
					
		

	}	
		
	}
}
	
