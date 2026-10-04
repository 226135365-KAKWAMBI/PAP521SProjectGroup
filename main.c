#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

void displayMainMenu(void) {
    printf("\n=========================================\n");
    printf("  MUNICIPAL FINANCIAL MANAGEMENT SYSTEM  \n");
    printf("=========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main(void) {
    int choice;

    do {
        displayMainMenu();

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input format. Enter a number between 1 and 6.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu(); break;
            case 3: supplierMenu(); break;
            case 4: assetMenu(); break;
            case 5: reportsMenu(); break;
            case 6: 
                printf("\nExiting system. Good Bye!\n"); 
                break;
            default: 
                printf("\n[Error] Invalid choice! Select between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
