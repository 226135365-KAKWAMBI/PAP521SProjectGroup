#ifndef EMPLOYEES_H
#define EMPLOYEES_H

typedef struct
{
    int employeeID;
    char name[50];
    char department[30];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;

} Employee;

void addEmployee();
void displayEmployees();
void searchEmployee();
void employeeMenu();

#endif
