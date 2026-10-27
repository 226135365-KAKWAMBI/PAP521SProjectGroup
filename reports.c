#include <stdio.h>
#include "utils.h"
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

/* Recursive total of gross salaries from index 'index' to the end. */
static double sumGrossSalaries(int index) {
    if (index >= employee_count) {
        return 0.0;
    }
    return employees[index].gross_salary + sumGrossSalaries(index + 1);
}

void generateEmployeeReport(void) {
    printf("\n=== EMPLOYEE REPORT ===\n");
    if (employee_count == 0) {
        printf("Total Employees: 0\n");
        return;
    }

    int hi = 0, lo = 0;
    for (int i = 1; i < employee_count; i++) {
        if (employees[i].gross_salary > employees[hi].gross_salary) hi = i;
        if (employees[i].gross_salary < employees[lo].gross_salary) lo = i;
    }

    double total = sumGrossSalaries(0);

    printf("Total Employees : %d\n", employee_count);
    printf("Total Payroll   : N$%.2f (gross)\n", total);
    printf("Average Salary  : N$%.2f\n", total / employee_count);
    printf("Highest Salary  : N$%.2f (%s)\n", employees[hi].gross_salary, employees[hi].name);
    printf("Lowest Salary   : N$%.2f (%s)\n", employees[lo].gross_salary, employees[lo].name);
}

void generateBudgetReport(void) {
    printf("\n=== BUDGET REPORT ===\n");
    if (budget_count == 0) {
        printf("No budget data available.\n");
        return;
    }

    double total_alloc = 0.0, total_exp = 0.0;
    for (int i = 0; i < budget_count; i++) {
        total_alloc += budgets[i].allocated_budget;
        total_exp   += budgets[i].expenditure;
    }

    printf("Total Allocated Budget : N$%.2f\n", total_alloc);
    printf("Total Expenditure      : N$%.2f\n", total_exp);
    printf("Remaining Budget       : N$%.2f\n", calculateBudget(total_alloc, total_exp));
    printf("Overall Status         : %s\n", getBudgetStatus(total_alloc, total_exp));

    displayBudgets();
    displayExceededDepartments();
}

void generateSupplierReport(void) {
    printf("\n=== SUPPLIER REPORT ===\n");
    displaySuppliers();
}

void generateAssetReport(void) {
    printf("\n=== ASSET REPORT ===\n");
    if (asset_count == 0) {
        printf("Total Assets: 0\n");
        return;
    }

    double total_val = 0.0;
    for (int i = 0; i < asset_count; i++) {
        total_val += assets[i].value;
    }

    printf("Total Registered Assets : %d\n", asset_count);
    printf("Total Asset Value       : N$%.2f\n", total_val);
    displayAssets();
}

void reportsMenu(void) {
    int choice;
    do {
        printf("\n--- REPORTS ---\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        choice = readMenuChoice("Enter choice: ", 5);

        switch (choice) {
            case 1: generateEmployeeReport(); break;
            case 2: generateBudgetReport();   break;
            case 3: generateSupplierReport(); break;
            case 4: generateAssetReport();    break;
            case 5: break;
        }
    } while (choice != 5);
}
