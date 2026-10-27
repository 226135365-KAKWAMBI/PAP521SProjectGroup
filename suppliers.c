#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "suppliers.h"

Supplier suppliers[MAX_SUPPLIERS];
int      supplier_count = 0;

int findSupplierIndex(const char *id) {
    for (int i = 0; i < supplier_count; i++) {
        if (strcmp(suppliers[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

static void printSupplierDetails(const Supplier *s) {
    printf("\n--- SUPPLIER DETAILS ---\n");
    printf("ID        : %s\n", s->id);
    printf("Name      : %s\n", s->name);
    printf("Email     : %s\n", s->email);
    printf("Telephone : %s\n", s->phone);
    printf("Town      : %s\n", s->town);
}

void addSupplier(void) {
    if (supplier_count >= MAX_SUPPLIERS) {
        printf("\n[Error] Supplier database limit (%d) reached!\n", MAX_SUPPLIERS);
        return;
    }

    Supplier s;
    printf("\n--- ADD SUPPLIER ---\n");

    for (;;) {
        readIdString("Enter Supplier ID: ", s.id, sizeof s.id);
        if (findSupplierIndex(s.id) != -1) {
            printf("[Error] A supplier with ID '%s' already exists.\n", s.id);
            continue;
        }
        break;
    }

    readNonEmptyString("Enter Supplier Name: ", s.name, sizeof s.name);

    for (;;) {
        readLine("Enter Email: ", s.email, sizeof s.email);
        if (!isValidEmail(s.email)) {
            printf("[Error] Invalid email (example: sales@company.com.na).\n");
            continue;
        }
        break;
    }

    for (;;) {
        readLine("Enter Telephone (7-15 digits, optional leading +): ", s.phone, sizeof s.phone);
        if (!isValidPhone(s.phone)) {
            printf("[Error] Invalid telephone number.\n");
            continue;
        }
        break;
    }

    readNonEmptyString("Enter Town/Location: ", s.town, sizeof s.town);

    suppliers[supplier_count++] = s;
    printf("\n[Success] Supplier added!\n");
}

void displaySuppliers(void) {
    if (supplier_count == 0) {
        printf("\n[Info] No supplier records found.\n");
        return;
    }

    printf("\n");
    printLine('=', 100);
    printf("%-8s %-20s %-28s %-16s %-16s\n", "ID", "Name", "Email", "Telephone", "Town");
    printLine('-', 100);

    for (int i = 0; i < supplier_count; i++) {
        printf("%-8.8s %-20.20s %-28.28s %-16.16s %-16.16s\n",
               suppliers[i].id, suppliers[i].name, suppliers[i].email,
               suppliers[i].phone, suppliers[i].town);
    }
    printLine('=', 100);
    printf("Total suppliers: %d\n", supplier_count);
}

/* Search by exact ID (strcmp) or part of the supplier name. */
void searchSupplier(void) {
    if (supplier_count == 0) {
        printf("\n[Info] Supplier database is empty.\n");
        return;
    }

    char key[SUPPLIER_STR_LEN];
    int found = 0;

    readNonEmptyString("\nEnter Supplier ID or part of the name: ", key, sizeof key);

    for (int i = 0; i < supplier_count; i++) {
        if (strcmp(suppliers[i].id, key) == 0 ||
            containsIgnoreCase(suppliers[i].name, key)) {
            printSupplierDetails(&suppliers[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\n[Info] No supplier matching '%s' found.\n", key);
    } else {
        printf("\n%d supplier(s) found.\n", found);
    }
}

/* Compare supplier locations: list every supplier in a given town. */
void searchSupplierByTown(void) {
    if (supplier_count == 0) {
        printf("\n[Info] Supplier database is empty.\n");
        return;
    }

    char town[SUPPLIER_STR_LEN];
    int found = 0;

    readNonEmptyString("\nEnter Town/Location: ", town, sizeof town);

    for (int i = 0; i < supplier_count; i++) {
        if (containsIgnoreCase(suppliers[i].town, town)) {
            printSupplierDetails(&suppliers[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\n[Info] No suppliers found in '%s'.\n", town);
    } else {
        printf("\n%d supplier(s) found in '%s'.\n", found, town);
    }
}

void supplierMenu(void) {
    int choice;
    do {
        printf("\n--- SUPPLIER MANAGEMENT ---\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search by ID or Name\n");
        printf("4. Search by Town/Location\n");
        printf("5. Back to Main Menu\n");
        choice = readMenuChoice("Enter choice: ", 5);

        switch (choice) {
            case 1: addSupplier();          break;
            case 2: displaySuppliers();     break;
            case 3: searchSupplier();       break;
            case 4: searchSupplierByTown(); break;
            case 5: break;
        }
    } while (choice != 5);
}
