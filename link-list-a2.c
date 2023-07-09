// Name: Sebastian Villafane Ramos / John Dang
// ID: 991647202 / 991659242
// Assignment 2 - Covid Link List : Main File

#include "link-list-a2.h" // include the link-list header file

int main()
{
    /* Declare and initialize necessary variables */ 
    ProvincePtr startPtr;       // creating list pointer
    startPtr = NULL;            // initialising the start of the list

    int provCount = 0;          // provCount contains number of entered provinces

    char provinceName[50];      // values for list structure objects
    char strTestCenters[6];         
    int numberOfTestCenters;
    int uniqueID;               // condition for unique ID verification

    puts("COVID-19 Provincial Infection Tracker\n-------------------------------------"); // Header/Title Line

    while (provCount < 13)
    {      
        uniqueID = 0;                                               // Initialize uniqueID for each loop iteration

        /* Get Province Name */
        printf("Enter Province Name: ");                            // request province name
        fgets(provinceName, 50, stdin);                             // read string here

        while (!uniqueID)                                           // ensure the province has yet to be entered
        {
            uniqueID = checkUniqueID(startPtr, provinceName);       // unique ID confirmation
        }

        /* Get Number of Test Centers */
        printf("Number of Test Centers: ");                         // request number of test centers                         
        fgets(strTestCenters, 6, stdin);                            // read string here
        numberOfTestCenters = validateTestCenters(strTestCenters);  // validate test centers to be 1-10

        /* Add province to the link list */ 
        startPtr = insertAndComputeTotalNumberOfInfections(startPtr, provinceName, numberOfTestCenters);
        provCount++;                                                // Increase province count
        printList(startPtr);                                        // display the list
        printf("\n");                                               // for formatting
    }

    /* Delete the list and display the province with the lowest number of infections */
    puts("All 13 provinces have been entered. Deleting the list...");   // Info line

    deleteAndDetermineLeastInfectedProvince(startPtr);                  // delete function call
} // end of main