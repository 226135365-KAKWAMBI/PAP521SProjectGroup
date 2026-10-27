#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS     50
#define BUDGET_STR_LEN  50

typedef struct {
    char   department_id[BUDGET_STR_LEN];
    char   department_name[BUDGET_STR_LEN];
    double allocated_budget;
    double expenditure;
    double remaining_budget;
} Budget;

extern Budget budgets[MAX_BUDGETS];
extern int    budget_count;

void        budgetMenu(void);
void        addBudget(void);
void        recordExpenditure(void);
void        displayBudgets(void);
void        searchBudget(void);
void        displayExceededDepartments(void);
int         countExceededDepartments(void);
int         findBudgetIndex(const char *id);
double      calculateBudget(double allocated, double expenditure);
const char *getBudgetStatus(double allocated, double expenditure);

#endif
