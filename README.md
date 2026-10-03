# Municipal Financial Management System (MFMS)

## Project Overview
This project is a C-based municipal financial management application developed for PAP521S (Programming in Practice) at the Namibia University of Science and Technology (NUST).

## Group Details
* **Course:** PAP521S - Programming in Practice
* **Development Environment:** VS Code + GCC
* **Language Standard:** ANSI C (C99)

## Team Members & Responsibilities
* **Student 1:** Employee Management Module (`employees.c`, `employees.h`)
* **Student 2:** Budget Management Module (`budget.c`, `budget.h`)
* **Student 3:** Supplier Management Module (`suppliers.c`, `suppliers.h`)
* **Student 4:** Asset Management Module (`assets.c`, `assets.h`)
* **Student 5:** Reports Module (`reports.c`, `reports.h`)
* **Student 6:** Main Integration & Data Validation (`main.c`)
* **Student 7:** Testing, Documentation, Git Coordination (`README.md`, Technical Report)

## System Features
* **Employee Management:** Add, search, view, and calculate net salary (Basic + Allowances).
* **Budget Management:** Track departmental budgets, log expenditure, and identify over-budget departments.
* **Supplier Management:** Maintain municipal supplier details with search capabilities.
* **Asset Management:** Record and search municipal equipment, vehicles, and assets.
* **Reports:** Generate summary data across all system modules.

## How to Compile and Run
Using GCC in terminal:
```bash
gcc -std=c99 main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms
./mfms 
That's our template
