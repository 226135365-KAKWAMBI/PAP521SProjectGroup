#include <stdio.h>
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

static void displayMainMenu(void) {
    printf("\n");
    printLine('=', 40);
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printLine('=', 40);
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

int main(void) {
    int choice;

    do {
        displayMainMenu();
        choice = readMenuChoice("Enter your choice: ", 6);

        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu();   break;
            case 3: supplierMenu(); break;
            case 4: assetMenu();    break;
            case 5: reportsMenu();  break;
            case 6: printf("\nExiting system. Goodbye!\n"); break;
        }
    } while (choice != 6);

    return 0;
}
