# Municipal Financial Management System (MFMS) - Project A

**Course:** PAP521S - Programming in Practice, NUST
**Group number:** ___
**Language / tools:** ANSI C (C99), Visual Studio Code, GCC, Git & GitHub

## Group members and responsibilities

| # | Student name | Student number | Responsibility |
|---|---|---|---|
| 1 | Vilio N Kakwambi | 226135365 | main.c, utils.c/h, GitHub setup, compiling and testing |
| 2 | Peter-John Einbeck | 219148457 | suppliers.c/h |
| 3 | Ngombe Mundukove | 226031837 | budget.c/h |
| 4 | Hamutenya SS | 223063932 | reports.c/h |
| 5 | Hamukwaya Jason | 221132147 | employees.c/h |
| 6 | Ndishimonima S | 221038507 | assets.c/h |

## Project description

A menu-driven console application for managing a municipality's employees and salaries, department budgets, suppliers and assets, with summary reports. Data is stored in arrays of structs in memory.

## System features

- Main menu with clear navigation and invalid-choice handling
- Employees: add, display, search (ID or name), salary calculation (basic + housing + transport, 7% deduction)
- Budget: department budgets, expenditure entry, remaining budget, WITHIN BUDGET / EXCEEDED status, departments over budget
- Suppliers: ID, name, email, telephone, town; add, display, search by ID/name and by town
- Assets: ID, name, type, purchase value, department, condition; add, display, search
- Reports: employee, budget, supplier and asset reports
- Validation: no negative values, no empty names, no duplicate IDs, email/phone checks

## Compilation

    gcc -std=c99 -Wall -Wextra -pedantic -o mfms main.c employees.c budget.c suppliers.c assets.c reports.c utils.c

Or run `make`.

## How to run

Windows: `.\mfms.exe`   Linux/macOS: `./mfms`