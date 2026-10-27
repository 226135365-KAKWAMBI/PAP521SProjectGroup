#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "employees.h"

Employee employees[MAX_EMPLOYEES];
int      employee_count = 0;

/* Returns index of employee with this exact ID, or -1 if not found. */
int findEmployeeIndex(const char *id) {
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

/* Calculates gross, deductions and net salary for one employee. */
void calculateSalary(Employee *e) {
    e->gross_salary = e->basic_salary + e->housing_allowance + e->transport_allowance;
    e->deductions   = e->gross_salary * DEDUCTION_RATE;
    e->net_salary   = e->gross_salary - e->deductions;
}

/* Builds "Name - Position (Department)" into out using strcpy/strcat. */
static void buildEmployeeLabel(char *out, const Employee *e) {
    strcpy(out, e->name);
    strcat(out, " - ");
    strcat(out, e->position);
    strcat(out, " (");
    strcat(out, e->department);
    strcat(out, ")");
}

static void printEmployeeDetails(const Employee *e) {
    char label[EMP_LABEL_LEN];
    buildEmployeeLabel(label, e);

    printf("\n--- EMPLOYEE DETAILS ---\n");
    printf("ID                  : %s\n", e->id);
    printf("Employee            : %s\n", label);
    printf("Basic Salary        : N$%.2f\n", e->basic_salary);
    printf("Housing Allowance   : N$%.2f\n", e->housing_allowance);
    printf("Transport Allowance : N$%.2f\n", e->transport_allowance);
    printf("Gross Salary        : N$%.2f\n", e->gross_salary);
    printf("Deductions (%.0f%%)    : N$%.2f\n", DEDUCTION_RATE * 100, e->deductions);
    printf("Net Salary          : N$%.2f\n", e->net_salary);
}

void addEmployee(void) {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("\n[Error] Employee database limit (%d) reached!\n", MAX_EMPLOYEES);
        return;
    }

    Employee e;
    printf("\n--- ADD EMPLOYEE ---\n");

    for (;;) {
        readIdString("Enter Employee ID: ", e.id, sizeof e.id);
        if (findEmployeeIndex(e.id) != -1) {
            printf("[Error] An employee with ID '%s' already exists.\n", e.id);
            continue;
        }
        break;
    }

    readPersonName("Enter Employee Name: ", e.name, sizeof e.name);
    readNonEmptyString("Enter Department: ", e.department, sizeof e.department);
    readNonEmptyString("Enter Position: ", e.position, sizeof e.position);
    e.basic_salary        = readDoubleInRange("Enter Basic Salary (N$): ", 0.01, 10000000.0);
    e.housing_allowance   = readDoubleInRange("Enter Housing Allowance (N$): ", 0.0, 10000000.0);
    e.transport_allowance = readDoubleInRange("Enter Transport Allowance (N$): ", 0.0, 10000000.0);

    calculateSalary(&e);
    employees[employee_count++] = e;

    printf("\n[Success] Employee added! Gross: N$%.2f | Net: N$%.2f\n",
           e.gross_salary, e.net_salary);
}

void displayEmployees(void) {
    if (employee_count == 0) {
        printf("\n[Info] No employee records found.\n");
        return;
    }

    printf("\n");
    printLine('=', 100);
    printf("%-8s %-18s %-14s %-14s %12s %12s %12s\n",
           "ID", "Name", "Department", "Position", "Basic", "Gross", "Net");
    printLine('-', 100);

    for (int i = 0; i < employee_count; i++) {
        printf("%-8.8s %-18.18s %-14.14s %-14.14s %12.2f %12.2f %12.2f\n",
               employees[i].id, employees[i].name, employees[i].department,
               employees[i].position, employees[i].basic_salary,
               employees[i].gross_salary, employees[i].net_salary);
    }
    printLine('=', 100);
    printf("Total employees: %d\n", employee_count);
}

/* Search by exact ID (strcmp) or by part of the name (case-insensitive). */
void searchEmployee(void) {
    if (employee_count == 0) {
        printf("\n[Info] Employee database is empty.\n");
        return;
    }

    char key[EMP_STR_LEN];
    int found = 0;

    readNonEmptyString("\nEnter Employee ID or part of the name: ", key, sizeof key);

    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].id, key) == 0 ||
            containsIgnoreCase(employees[i].name, key)) {
            printEmployeeDetails(&employees[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\n[Info] No employee matching '%s' found.\n", key);
    } else {
        printf("\n%d employee(s) found.\n", found);
    }
}

void showSalaryInformation(void) {
    if (employee_count == 0) {
        printf("\n[Info] Employee database is empty.\n");
        return;
    }

    char id[EMP_STR_LEN];
    readIdString("\nEnter Employee ID: ", id, sizeof id);

    int idx = findEmployeeIndex(id);
    if (idx == -1) {
        printf("\n[Info] No employee with ID '%s' found.\n", id);
        return;
    }

    const Employee *e = &employees[idx];
    printf("\n--- SALARY INFORMATION: %s ---\n", e->name);
    printf("Basic Salary        : N$%10.2f\n", e->basic_salary);
    printf("+ Housing Allowance : N$%10.2f\n", e->housing_allowance);
    printf("+ Transport Allow.  : N$%10.2f\n", e->transport_allowance);
    printf("= Gross Salary      : N$%10.2f\n", e->gross_salary);
    printf("- Deductions (%.0f%%)  : N$%10.2f\n", DEDUCTION_RATE * 100, e->deductions);
    printf("= NET SALARY        : N$%10.2f\n", e->net_salary);
    printf("Annual Gross Salary : N$%10.2f\n", e->gross_salary * 12);
}

void employeeMenu(void) {
    int choice;
    do {
        printf("\n--- EMPLOYEE MANAGEMENT ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Salary Information\n");
        printf("5. Back to Main Menu\n");
        choice = readMenuChoice("Enter choice: ", 5);

        switch (choice) {
            case 1: addEmployee();          break;
            case 2: displayEmployees();     break;
            case 3: searchEmployee();       break;
            case 4: showSalaryInformation(); break;
            case 5: break;
        }
    } while (choice != 5);
}
