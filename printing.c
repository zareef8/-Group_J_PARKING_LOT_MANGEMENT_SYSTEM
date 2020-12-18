#include <stdio.h>
#include <stdlib.h>

#include "printing.h"
#include "datamanagement.h"

char profile_data[50];

char* DisplayDriverProfile(DriverProfile* profile) 
{
    sprintf_s(profile_data, "Name:%s\nLicense plate:%s\n", profile->name, profile->license_plate);

    return profile_data;
}


char* DisplayParkingProfile(ParkingProfile* profile) 
{
    sprintf_s(profile_data, "LicenseNumber:%i, Parkspace:%i", profile->parked->license_plate, profile->parkSpace);

    return profile_data;
}


void DisplayAllDriverProfileData(DriverProfile* first_profile) 
{
    if (first_profile == NULL) {
        printf("Profile is empty");
        return;
    }

    struct DriverProfile* next = first_profile;

    for (; next != NULL; next = next->next) {

        printf("Name: %s\nLicense_plate: %s\n", next->name, next->license_plate);
    }
}


void DisplayAllParkingProfileData(ParkingProfile* first_profile) 
{
    if (first_profile == NULL) {
        printf("Profile is empty");
        return;
    }

    struct ParkingProfile* next = first_profile;

    for (; next != NULL; next = next->next) {

        printf_s("License Number: %i\n", next->parked->license_plate);
    }
}