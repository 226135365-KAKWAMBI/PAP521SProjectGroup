#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "budget.h"

Budget budgets[MAX_BUDGETS];
int    budget_count = 0;

int findBudgetIndex(const char *id) {
    for (int i = 0; i < budget_count; i++) {
        if (strcmp(budgets[i].department_id, id) == 0) {
            return i;
        }
    }
    return -1;
}

/* Returns the remaining budget (negative means overspent). */
double calculateBudget(double allocated, double expenditure) {
    return allocated - expenditure;
}

/* Decides whether spending is within the allocated budget. */
const char *getBudgetStatus(double allocated, double expenditure) {
    if (expenditure > allocated) {
        return "EXCEEDED";
    }
    return "WITHIN BUDGET";
}

static void printBudgetDetails(const Budget *b) {
    printf("\nDepartment        : %s (%s)\n", b->department_name, b->department_id);
    printf("Allocated Budget  : N$%.2f\n", b->allocated_budget);
    printf("Expenditure       : N$%.2f\n", b->expenditure);
    printf("Remaining Budget  : N$%.2f\n", b->remaining_budget);
    printf("Status            : %s\n", getBudgetStatus(b->allocated_budget, b->expenditure));
}

void addBudget(void) {
    if (budget_count >= MAX_BUDGETS) {
        printf("\n[Error] Budget database limit (%d) reached!\n", MAX_BUDGETS);
        return;
    }

    Budget b;
    printf("\n--- ADD DEPARTMENT BUDGET ---\n");

    for (;;) {
        readIdString("Enter Department ID: ", b.department_id, sizeof b.department_id);
        if (findBudgetIndex(b.department_id) != -1) {
            printf("[Error] Department ID '%s' already has a budget.\n", b.department_id);
            continue;
        }
        break;
    }

    readNonEmptyString("Enter Department Name: ", b.department_name, sizeof b.department_name);
    b.allocated_budget = readDoubleInRange("Enter Allocated Budget (N$): ", 0.01, 1000000000000.0);
    b.expenditure      = 0.0;
    b.remaining_budget = calculateBudget(b.allocated_budget, b.expenditure);

    budgets[budget_count++] = b;
    printf("\n[Success] Budget added! Use 'Enter Expenditure' to record spending.\n");
}

void recordExpenditure(void) {
    if (budget_count == 0) {
        printf("\n[Info] No budgets found. Add a department budget first.\n");
        return;
    }

    char id[BUDGET_STR_LEN];
    readIdString("\nEnter Department ID: ", id, sizeof id);

    int idx = findBudgetIndex(id);
    if (idx == -1) {
        printf("\n[Info] Department ID '%s' not found.\n", id);
        return;
    }

    double amount = readDoubleInRange("Enter Expenditure Amount (N$): ", 0.0, 1000000000000.0);

    budgets[idx].expenditure += amount;
    budgets[idx].remaining_budget =
        calculateBudget(budgets[idx].allocated_budget, budgets[idx].expenditure);

    printf("\n[Success] Expenditure recorded.");
    printBudgetDetails(&budgets[idx]);

    if (budgets[idx].expenditure > budgets[idx].allocated_budget) {
        printf("\n[WARNING] %s has exceeded its budget by N$%.2f!\n",
               budgets[idx].department_name, -budgets[idx].remaining_budget);
    }
}

void displayBudgets(void) {
    if (budget_count == 0) {
        printf("\n[Info] No budget records found.\n");
        return;
    }

    printf("\n");
    printLine('=', 96);
    printf("%-8s %-18s %16s %16s %16s  %-13s\n",
           "ID", "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printLine('-', 96);

    for (int i = 0; i < budget_count; i++) {
        printf("%-8.8s %-18.18s %16.2f %16.2f %16.2f  %-13s\n",
               budgets[i].department_id, budgets[i].department_name,
               budgets[i].allocated_budget, budgets[i].expenditure,
               budgets[i].remaining_budget,
               getBudgetStatus(budgets[i].allocated_budget, budgets[i].expenditure));
    }
    printLine('=', 96);
}

void searchBudget(void) {
    if (budget_count == 0) {
        printf("\n[Info] Budget database is empty.\n");
        return;
    }

    char key[BUDGET_STR_LEN];
    int found = 0;

    readNonEmptyString("\nEnter Department ID or part of the name: ", key, sizeof key);

    for (int i = 0; i < budget_count; i++) {
        if (strcmp(budgets[i].department_id, key) == 0 ||
            containsIgnoreCase(budgets[i].department_name, key)) {
            printBudgetDetails(&budgets[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\n[Info] No department matching '%s' found.\n", key);
    }
}

int countExceededDepartments(void) {
    int count = 0;
    for (int i = 0; i < budget_count; i++) {
        if (strcmp(getBudgetStatus(budgets[i].allocated_budget, budgets[i].expenditure),
                   "EXCEEDED") == 0) {
            count++;
        }
    }
    return count;
}

void displayExceededDepartments(void) {
    int count = countExceededDepartments();

    if (count == 0) {
        printf("\nNo departments have exceeded their budget.\n");
        return;
    }

    printf("\nDEPARTMENTS THAT EXCEEDED THEIR BUDGET (%d):\n", count);
    for (int i = 0; i < budget_count; i++) {
        if (budgets[i].expenditure > budgets[i].allocated_budget) {
            printf("  - %s (%s): allocated N$%.2f, spent N$%.2f, over by N$%.2f\n",
                   budgets[i].department_name, budgets[i].department_id,
                   budgets[i].allocated_budget, budgets[i].expenditure,
                   -budgets[i].remaining_budget);
        }
    }
}

void budgetMenu(void) {
    int choice;
    do {
        printf("\n--- BUDGET MANAGEMENT ---\n");
        printf("1. Add Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Display Budgets\n");
        printf("4. Search Budget\n");
        printf("5. Show Departments Over Budget\n");
        printf("6. Back to Main Menu\n");
        choice = readMenuChoice("Enter choice: ", 6);

        switch (choice) {
            case 1: addBudget();                  break;
            case 2: recordExpenditure();          break;
            case 3: displayBudgets();             break;
            case 4: searchBudget();               break;
            case 5: displayExceededDepartments(); break;
            case 6: break;
        }
    } while (choice != 6);
}
