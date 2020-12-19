# Group_J_PARKING_LOT_MANGEMENT_SYSTEM #

This software project is a part of the fullfilment for the course SYSC5709 Softwatre Development in C at Carleton University. The program is a parking lot management system which will help parking lot owners to manage thier lots effectively and efficiently. 

# Description #
The program consists of features for both an Admins and the Clients of the parking lot. 
The program keeps records of all the vehicles entering and exiting the parking lot at all times. 
The current status of the parking lot can be seen i.e The number of spots left. 
There is an automatic calcualtion of the payment based on the system time.
Admins of the lot can login using a password and will be able access features like blacklisting vehicles,searching vehicles,Display vehicle information,etc.
Admis can also see certain reports for the parking lot like: The average time parked, the standard deviation and displaying vehicles fot the last 30 days.
More infornmation about the features and how to use them is given in the Usage section.


# Installation # 


# Usage #
After Running the program the  welcome screen is shown. Press any key to view the main startup menu :

![mysc](https://user-images.githubusercontent.com/71241275/102698139-24888e00-4209-11eb-80d7-6227cf06722a.jpg)

The program will allow you to choose from the following options 1,2 and 3 as shown.
After the choice is entered the following occurs depending on the choice.

### Enter as Admin ###
If selection is 1: The "Enter as Admin" feature is chosen. Next, the program will ask for the fixed admin password which is "111".
After entering the correct password you will be able to access the admin menu which is shown below and can enter your choice from 1-6 to select from the given features

![admin](https://user-images.githubusercontent.com/71241275/102698223-da53dc80-4209-11eb-8e31-017ef75903f5.jpg)


##### Display current Vehicles
If selection is 1: "Display current Vehicles" feature is chosen and the program will display all information for vehciles which are currently parked in the lot. Press any key to go back to the main startup menu.
##### Display all Drivers profile data
If selection is 2: "Display all Drivers profile data" feature is chosen and the program will display all information for all vechiles which have entered the parking lot. Therefore, it will show the information of current vechiles in the lot as well as information of any departed vehicles which previously entered the lot.Press any key to go back to the main startup menu.
##### Search a vehcile by license Plate number
If selection is 3: "Search a vehcile by license Plate number" fearure is chosen and the program will ask to enter a vehicle license plate. A valid license plate which is stored in the system must be entered for successful execution of this search feature. If an invalid license plate is entered the program will display "Vehicles not Found in Database". If a valid license plate is entered the program will display all the information for that particular vehicle.In either case, press any key to go back to the main startup menu.
##### Delete All Records
If selection is 4: "Delete All Records" feature is chosen and the program will delete all stored information and display "All content of file Deleted". Press any key to go back to the main startup menu.
##### Blacklist
If selection is 5: "Blacklist" feature is chosen and the pogram will take you to the blacklist menu as shown. From there there will be three options to choose from:
  
  ![blacklist](https://user-images.githubusercontent.com/71241275/102698292-47677200-420a-11eb-8775-678766cc2d40.jpg)

  If selection is 1: "Black List Vehicle " is chosen and the prgoram will allow the admin to enter a valid license plate and and blacklist the vehicle. This will make   sure the blacklisted vehicle cannot enter the lot unitl the vehicle removed from the blacklist.If an invalid license plate is given the program will display "Error   ! Data not found.".Press any key to go back to the main startup menu.
 
  If selection is 2: "Remove From Blacklist" is chosen, the program will allow the admin to enter a valid license plate which is already blacklisted to be removed       from the list.If an invalid license plate is given the program will display "Error   ! Data not found". Press any key to go back to the main startup menu.
  
  If selection is 3: "Show all Black listed Vehicles" is chosen and the program will display the information of all the vehicles which are blacklisted. If there are     no vehicles which are blacklisted, "No blacklisted vehicles exist in database" will be displayed. Press any key to go back to the main startup menu.
##### Reports
If the selection is 6: "Reports" feature is chosen and the program will take the admin to the reports menu where there are three options to choose from.

![reports](https://user-images.githubusercontent.com/71241275/102698335-931a1b80-420a-11eb-9ff5-bc14072b2e77.jpg)


  If the selection is 1: "Standard Deviation" is chosen and the program will return the standard deviation of the total parked time of all vehicles which have parked   in the lot. Press any key to go back to the main startup menu.
  
  If the selection is 2: "Average park time" is chosen and the program will display the average of the total time of park for all vehicles which have parked in the     lot. Press any key to go back to the main startup menu.
  
  If the selection is 3: "Show past 30 Days Records" is chosen and the program will display information for all vechiles which have their information stored in the     last 30days. Press any key to go back to the main startup menu.

### Enter as Customer ####
In the main start up menu if the selection is 2 "Enter as Customer" feature is chosen and a customer menu is shown where there are four options to choose from.
##### Arrival of a Vehicle
  If the selection is 1: "Arrival of a Vehicle" feature is chosen and this means the customer wants to enter the parking lot. The program will ask for their name and   license plate which will be used to record thier information and upon successful entry "Vehicle parked successfully" will be displayed. Press any key to go back to   the main startup menu.
##### Departure of a Vehicle  
  If the selection is 2: "Departure of a Vehicle" feature is chosen and is used when a customer wants to exit their vehicle from the parking lot. The program will ask   for a valid license plate. Upon entering a valid license plate the program displays if the customer had a pass or not and displays the total time parked and how       much they have to pay based on their stay. "Vehicle Departed Successfully" is played at the end. Press any key to go back to the main startup menu.
##### Number of spaces available  
  If the selection is 3: "Number of space available" feature is chosen and the program displays the total number of parking spots available in the lot. Press any key   to go back to the main startup menu.
##### Add monthly pass
  If the selection is 4: "Add monthly Pass" feature is chosen and the program will ask to enter customer name and license plate which must be valid and exist in the     record. If the inputs are valid the pprogram will ask to enter Y or N to purchase a 100 dollar monthly pass. If Y is chosen the pass is added to the customer if N     is chosen then pass is not added.Press any key to go back to the main startup menu.


# Credits 


# License 
