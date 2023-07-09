// Name: Sebastian Villafane Ramos / John Dang
// ID: 991647202 / 991659242
// Assignment 2 - Covid Link List : Header File

// Header file containing link-list definitions & implementation methods
#include <stdio.h>
#include <stdlib.h> // malloc() and free() are found here
#include <string.h>

/* Structure Definition */ 
struct province
{
    char provinceName[50];
    unsigned int numberOfTestCenters;
    unsigned int totalNumberOfInfections;
    struct province *nextPtr;
};

/* Structure renaming */
typedef struct province Province;
typedef struct province *ProvincePtr;

/* Function prototypes */ 
ProvincePtr makeProvince(char name[50], unsigned int testCenterTotal, unsigned int infectionCount);

ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[50], int numberOfTestCenters);

void deleteAndDetermineLeastInfectedProvince(ProvincePtr listPtr);

void printList(ProvincePtr listPtr);                            // Display all the info in the linked list

int validateTestCenters(char strValue[6]);                      // Ensure test center value is between 1-10

int checkUniqueID(ProvincePtr listPtr, char provinceName[50]);  // Ensure the province has not been entered already


/*******Function Definitions******/
ProvincePtr makeProvince(char name[50], unsigned int testCenterTotal, unsigned int infectionCount)
{
    /* Create a new instance of province */ 
    ProvincePtr newPtr;
    newPtr = (ProvincePtr)malloc(sizeof(Province));
    if (newPtr != NULL)
    {
        strcpy(newPtr->provinceName, name);             // strcpy required to copy a string value
        newPtr->numberOfTestCenters = testCenterTotal;
        newPtr->totalNumberOfInfections = infectionCount;
        newPtr->nextPtr = NULL;
    }
    else
    {
        puts("Memory Issue... Province not created");   // error creating instance
    }
    return newPtr;
}

ProvincePtr insertAndComputeTotalNumberOfInfections(ProvincePtr listPtr, char provinceName[50], int numberOfTestCenters)
{
    /* Declare pointers and variables */
    ProvincePtr newPtr, previousPtr, currentPtr;
    unsigned int infectionCount = 0;
    char inputNum[6];

    /* Loop through the given number of test centers to calculate the total number of infections */
    for (unsigned int i = 1; i <= numberOfTestCenters; i++)
    {
        
        printf("Test Center #%u: ", i);                     // ask user for num of infections at test center
        fgets(inputNum, 6, stdin);                          // read string here
        infectionCount += (int)strtol(inputNum, NULL, 0);   // converts stringValue to integer and accumulate infections
    }

    /* Initialize pointers */ 
    newPtr = makeProvince(provinceName, numberOfTestCenters, infectionCount);   // Create a province with the calculated value
    previousPtr = NULL;
    currentPtr = listPtr;

    /* Loop through the list to place the province based on alphabetical order */
    while (currentPtr != NULL && strcmp(newPtr->provinceName, currentPtr->provinceName) > 0 )
    {
        previousPtr = currentPtr;           // move previous pointer
        currentPtr = currentPtr->nextPtr;   // move current pointer to the next pointer
    }
    
    if (previousPtr == NULL)        // Front of the list
    {
        newPtr->nextPtr = listPtr;      // make the next pointer of the first province be location at the start of the list
        listPtr = newPtr;               // change the start of the list to be the new provinces location
    }
    else                            // Elsewhere in the list (middle or end)
    {                                  
        previousPtr->nextPtr = newPtr; // previous pointers next pointer is the new pointer
        newPtr->nextPtr = currentPtr;  // new pointers next pointer is current pointer
    }

    return listPtr;     // advertise address changes to other actors
}

void deleteAndDetermineLeastInfectedProvince(ProvincePtr listPtr)
{
    /* Declare and initialize necessary variables */
    ProvincePtr tempPtr = NULL, currentPtr = listPtr;
    unsigned int lowestCases = currentPtr->totalNumberOfInfections;
    char province[50];

    /* Loop through list and free the nodes */
    if (listPtr == NULL) // check if list is empty
    {
        puts("List is empty... nothing to remove");
    }
    while (currentPtr != NULL)
    {   
        // Save the name and total of the province with the lowest cases
        if (currentPtr->totalNumberOfInfections <= lowestCases)
        {
            lowestCases = currentPtr->totalNumberOfInfections;
            strcpy(province, currentPtr->provinceName);
        }
        // iterate through the list
        tempPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
        free(tempPtr); // free the space
    }

    /* Print data */
    printf("\n%s has the lowest number of cases(%u)\n", province, lowestCases);
}

void printList(ProvincePtr sPtr)
{
    ProvincePtr currentPtr = sPtr;  // Delcare and initialize current ptr

    /* Iterate through the list and print values*/
    if (currentPtr == NULL) // check if list is empty
    {
        puts("List is empty... nothing to print");
        return;
    }
    else
    {
        puts("\n==========List of Provinces==========\n");  // Header divisor
        while (currentPtr != NULL)
        {
            /* Display values */
            printf("Province: %s\n", currentPtr->provinceName);
            printf("Number of Test Centers: %u\n", currentPtr->numberOfTestCenters);
            printf("Total Number of Infections: %u\n", currentPtr->totalNumberOfInfections);

            puts("");                                       // for spacing purposes
            currentPtr = currentPtr->nextPtr;               // go to the next item
        }
        puts("=====================================");      // Footer divisor
    }
}

int validateTestCenters(char strValue[6])
{
    int intValue = (int)strtol(strValue, NULL, 0);  // turn the string value from fgets to an int

    while (intValue < 1 || intValue > 10)           // continue to ask for number of test centers until it is between 1-10
    {
        char temp[6];           // Temporary string 
        printf("Invalid Value. Please enter a number between 1-10: ");
        fgets(temp, 6, stdin);
        intValue = (int)strtol(temp, NULL, 0);
    }

    return intValue;
}

int checkUniqueID(ProvincePtr listPtr, char provinceName[50]) // returns bool for the while loop condition inside the main
{
    /* Declare and initialize necessary pointers */ 
    ProvincePtr tempPtr = NULL, previousPtr = NULL, currentPtr = listPtr;

    /* Format the province name by removing new line characters to avoid funky display errors */ 
    if (provinceName[strlen(provinceName) - 1] == '\n')
    {
        provinceName[strlen(provinceName) - 1] = '\0'; // convert \n to null
    }

    /* Loop through the list to check all the names */
    if (listPtr == NULL)    // check if list is empty
    {
        return 1;           // return 1 to exit the while loop
    }
    while (currentPtr != NULL)
    {
        if (strcmp(currentPtr->provinceName, provinceName) == 0)    // if the province entered by the user is already in the list
        {
            printf("This province has already been entered.\nEnter a different province: ");    // ask them to enter a different province
            fgets(provinceName, 50, stdin);                                                     // read string here
            return 0;                                                                           // return 0 to stay in the while loop
        }
        // iterate through the list
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }
    
    return 1;   // return 1 to exit the while loop
}