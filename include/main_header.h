/**
*@file main_header.h
*
*@brief Contains information for all functions to use
*
**/
#ifndef MAIN_HEADER_H_INCLUDED
#define MAIN_HEADER_H_INCLUDED
/**@details The constant hour is the rate of payment for parking.
* The constant Capacity is the set capacity of the parking lot.
* The string pass is the fixed admin password.
*
* The structure Customer is used to hold customer information.
* The following information is stored for a customer:
* Name
* License Plate
* Status (Parked/ Departed)
* Entry time
* Exit time
* Has Monthly pass or not
* Is Blacklisted or not
* Total time parked
* Price of parking paid
**/
#define hour 0.167
#define Capacity 100

char pass[] = "111";
struct Admin
{
	char password[20];
}admin;
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
#endif // MAIN_HEADER_H_INCLUDED
