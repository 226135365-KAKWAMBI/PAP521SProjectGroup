#include <stdio.h>
#include <string.h>
#include "EMPLOYEES.h"

Employee employees[100];
int employeeCount = 0;


    // ADD EMPLOYEE //
void addEmployee()
{
    printf("\nEmployee ID: ");
    scanf("%d", &employees[employeeCount].employeeID);

    printf("Employee Name: ");
    scanf("%s", employees[employeeCount].name);

    printf("Department: ");
    scanf("%s", employees[employeeCount].department);

    printf("Basic Salary: ");
    scanf("%lf", &employees[employeeCount].basicSalary);

    printf("Housing Allowance: ");
    scanf("%lf", &employees[employeeCount].housingAllowance);

    printf("Transport Allowance: ");
    scanf("%lf", &employees[employeeCount].transportAllowance);

    employeeCount++;

    printf("Employee added successfully.\n");
}


    // DISPLAY EMPLOYEES //
void displayEmployees()
{
    int i;

    printf("\n--- EMPLOYEES ---\n");
    for(i = 0; i < employeeCount; i++)
    {
        printf("\nID: %d", employees[i].employeeID);

        printf("\nName: %s", employees[i].name);

        printf("\nDepartment: %s", employees[i].department);

        printf("\nBasic Salary: %.2lf", employees[i].basicSalary);

        printf("\nHousing Allowance: %.2lf", employees[i].housingAllowance);

        printf("\nTransport Allowance: %.2lf\n", employees[i].transportAllowance);
    }
}


    // SEARCH EMPLOYEE //
void searchEmployee()
{
    int i;
    int searchID;

    printf("Enter Employee ID: ");
    scanf("%d", &searchID);

    for(i = 0; i < employeeCount; i++)
    {
        if(employees[i].employeeID == searchID)
        {
            printf("\nEmployee Found!\n");

            printf("Name: %s\n", employees[i].name);

            printf("Department: %s\n", employees[i].department);

            printf("Basic Salary: %.2lf\n", employees[i].basicSalary);

            printf("Housing Allowance: %.2lf\n", employees[i].housingAllowance);

            printf("Transport Allowance: %.2lf\n", employees[i].transportAllowance);

            return;
        }
    }

    printf("Employee not found.\n");
}


    // EMPLOYEE MENU //
void employeeMenu()
{
    int choice;

    do
    {
        printf("\n1. Add Employee");
        printf("\n2. Display Employees");
        printf("\n3. Search Employee");
        printf("\n4. Exit");

        printf("\nChoice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 4);
}
