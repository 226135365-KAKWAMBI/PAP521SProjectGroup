#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS     50
#define SUPPLIER_STR_LEN  50

typedef struct {
    char id[SUPPLIER_STR_LEN];
    char name[SUPPLIER_STR_LEN];
    char email[SUPPLIER_STR_LEN];
    char phone[SUPPLIER_STR_LEN];
    char town[SUPPLIER_STR_LEN];
} Supplier;

extern Supplier suppliers[MAX_SUPPLIERS];
extern int      supplier_count;

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void searchSupplierByTown(void);
int  findSupplierIndex(const char *id);

#endif
