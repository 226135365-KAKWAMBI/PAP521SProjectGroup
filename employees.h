#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES   100
#define EMP_STR_LEN     50
#define EMP_LABEL_LEN   200
#define DEDUCTION_RATE  0.07   /* 7% pension / social security deduction */

typedef struct {
    char   id[EMP_STR_LEN];
    char   name[EMP_STR_LEN];
    char   department[EMP_STR_LEN];
    char   position[EMP_STR_LEN];
    double basic_salary;
    double housing_allowance;
    double transport_allowance;
    double gross_salary;     /* calculated */
    double deductions;       /* calculated */
    double net_salary;       /* calculated */
} Employee;

extern Employee employees[MAX_EMPLOYEES];
extern int      employee_count;

void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void showSalaryInformation(void);
void calculateSalary(Employee *e);
int  findEmployeeIndex(const char *id);

#endif
