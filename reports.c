#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void generateEmployeeReport(void) {
    printf("\n=== EMPLOYEE SUMMARY REPORT ===\n");
    if (employee_count == 0) {
        printf("Total Employees: 0\n");
        return;
    }

    double total = 0.0;
    double highest = employees[0].net_salary;
    double lowest = employees[0].net_salary;

    for (int i = 0; i < employee_count; i++) {
        double current = employees[i].net_salary;
        total += current;
        if (current > highest) highest = current;
        if (current < lowest) lowest = current;
    }

    printf("Total Employees : %d\n", employee_count);
    printf("Average Salary  : N$%.2f\n", total / employee_count);
    printf("Highest Salary  : N$%.2f\n", highest);
    printf("Lowest Salary   : N$%.2f\n", lowest);
}

void generateBudgetReport(void) {
    printf("\n=== BUDGET SUMMARY REPORT ===\n");
    if (budget_count == 0) {
        printf("No budget data available.\n");
        return;
    }

    double total_alloc = 0.0, total_exp = 0.0;
    int exceeded = 0;

    for (int i = 0; i < budget_count; i++) {
        total_alloc += budgets[i].allocated_budget;
        total_exp += budgets[i].expenditure;
        if (budgets[i].remaining_budget < 0) {
            exceeded++;
        }
    }

    printf("Total Allocated Budget : N$%.2f\n", total_alloc);
    printf("Total Expenditure      : N$%.2f\n", total_exp);
    printf("Remaining Balance      : N$%.2f\n", total_alloc - total_exp);
    printf("Departments Exceeded   : %d\n", exceeded);
}

void generateSupplierReport(void) {
    printf("\n=== SUPPLIER SUMMARY REPORT ===\n");
    printf("Total Registered Suppliers: %d\n", supplier_count);
    displaySuppliers();
}

void generateAssetReport(void) {
    printf("\n=== ASSET SUMMARY REPORT ===\n");
    if (asset_count == 0) {
        printf("Total Assets: 0\n");
        return;
    }

    double total_val = 0.0;
    for (int i = 0; i < asset_count; i++) {
        total_val += assets[i].value;
    }

    printf("Total Registered Assets: %d\n", asset_count);
    printf("Total Asset Value      : N$%.2f\n", total_val);
    displayAssets();
}

void reportsMenu(void) {
    int choice;
    do {
        printf("\n--- SYSTEM REPORTS ---\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("[Error] Enter a valid menu number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: generateEmployeeReport(); break;
            case 2: generateBudgetReport(); break;
            case 3: generateSupplierReport(); break;
            case 4: generateAssetReport(); break;
            case 5: break;
            default: printf("[Error] Choice must be between 1 and 5.\n");
        }
    } while (choice != 5);
}
