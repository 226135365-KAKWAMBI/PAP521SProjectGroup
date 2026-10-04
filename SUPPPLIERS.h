#ifndef SUPPLIERS_H
#define SUPPLIERS_H

typedef struct
{
    int supplierID;
    char name[50];
    char email[50];
    char phone[20];
    char town[30];
} Supplier;

void addSupplier();
void displaySuppliers();
void searchSupplier();
void compareSuppliers();
void supplierMenu();

#endif  
