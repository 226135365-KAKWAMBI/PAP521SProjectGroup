#include <string.h>
#include <stdio.h>
#include "SUPPLIERS.h"

Supplier suppliers[100];
int supplierCount = 0;

    //ADD SUPLLIER//
    void addSupplier()
{
    printf("\nSupplier ID: ");
    scanf("%d", &suppliers[supplierCount].supplierID);

    printf("Supplier Name: ");
    scanf("%s", suppliers[supplierCount].name);

    printf("Email: ");
    scanf("%s", suppliers[supplierCount].email);

    printf("Phone: ");
    scanf("%s", suppliers[supplierCount].phone);

    printf("Town: ");
    scanf("%s", suppliers[supplierCount].town);

    supplierCount++;

    printf("Supplier added successfully.\n");
}

    //DISPLAY SUPPLIER//
    void displaySuppliers()
{
    int i;

    printf("\n--- SUPPLIERS ---\n");

    for(i = 0; i < supplierCount; i++)
    {
        printf("\nID: %d", suppliers[i].supplierID);

        printf("\nName: %s", suppliers[i].name);

        printf("\nEmail: %s", suppliers[i].email);

        printf("\nPhone: %s", suppliers[i].phone);

        printf("\nTown: %s\n", suppliers[i].town);
    }
}

    //SEARCH SUPPLIERS//
    void searchSupplier()
{
    int i;
    int searchID;

    printf("Enter Supplier ID: ");
    scanf("%d", &searchID);

    for(i = 0; i < supplierCount; i++)
    {
        if(suppliers[i].supplierID == searchID)
        {
            printf("\nSupplier Found!\n");
            printf("Name: %s\n", suppliers[i].name);

            printf("Email: %s\n", suppliers[i].email);

            printf("Phone: %s\n", suppliers[i].phone);

            printf("Town: %s\n", suppliers[i].town);

            return;
        }
    }

    printf("Supplier not found.\n");
}

    //COMPARE SUPPLIERS//
    void compareSuppliers()
{
    int i;

    printf("\nSUPPLIERS FROM WINDHOEK\n");

    for(i = 0; i < supplierCount; i++)
    {
        if(strcmp(suppliers[i].town, "Windhoek") == 0)
        {
            printf("%s\n", suppliers[i].name);
        }
    }
}

    //MENU//
    void supplierMenu()
{
    int choice;

    do
    {
        printf("\n1. Add Supplier");
        printf("\n2. Display Suppliers");
        printf("\n3. Search Supplier");
        printf("\n4. Compare Suppliers");
        printf("\n5. Exit");

        printf("\nChoice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addSupplier();
                break;

            case 2:
                displaySuppliers();
                break;

            case 3:
                searchSupplier();
                break;

            case 4:
                compareSuppliers();
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 5);
}
