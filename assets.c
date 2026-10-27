#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "assets.h"

Asset assets[MAX_ASSETS];
int   asset_count = 0;

static const char *ASSET_TYPES[]  = { "Vehicle", "Computer", "Building", "Equipment", "Office Furniture" };
static const int   ASSET_TYPE_COUNT = 5;
static const char *CONDITIONS[]   = { "Excellent", "Good", "Fair", "Poor" };
static const int   CONDITION_COUNT = 4;

int findAssetIndex(const char *id) {
    for (int i = 0; i < asset_count; i++) {
        if (strcmp(assets[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

static void printAssetDetails(const Asset *a) {
    printf("\n--- ASSET DETAILS ---\n");
    printf("ID             : %s\n", a->id);
    printf("Name           : %s\n", a->name);
    printf("Type           : %s\n", a->type);
    printf("Purchase Value : N$%.2f\n", a->value);
    printf("Department     : %s\n", a->department);
    printf("Condition      : %s\n", a->condition);
}

void addAsset(void) {
    if (asset_count >= MAX_ASSETS) {
        printf("\n[Error] Asset database limit (%d) reached!\n", MAX_ASSETS);
        return;
    }

    Asset a;
    printf("\n--- ADD ASSET ---\n");

    for (;;) {
        readIdString("Enter Asset ID: ", a.id, sizeof a.id);
        if (findAssetIndex(a.id) != -1) {
            printf("[Error] An asset with ID '%s' already exists.\n", a.id);
            continue;
        }
        break;
    }

    readNonEmptyString("Enter Asset Name: ", a.name, sizeof a.name);

    printf("Asset Type:\n");
    for (int i = 0; i < ASSET_TYPE_COUNT; i++) {
        printf("  %d. %s\n", i + 1, ASSET_TYPES[i]);
    }
    printf("  %d. Other (type your own)\n", ASSET_TYPE_COUNT + 1);
    int t = readMenuChoice("Select type: ", ASSET_TYPE_COUNT + 1);
    if (t <= ASSET_TYPE_COUNT) {
        strcpy(a.type, ASSET_TYPES[t - 1]);
    } else {
        readNonEmptyString("Enter asset type: ", a.type, sizeof a.type);
    }

    a.value = readDoubleInRange("Enter Purchase Value (N$): ", 0.0, 1000000000000.0);
    readNonEmptyString("Enter Department: ", a.department, sizeof a.department);

    printf("Condition:\n");
    for (int i = 0; i < CONDITION_COUNT; i++) {
        printf("  %d. %s\n", i + 1, CONDITIONS[i]);
    }
    int c = readMenuChoice("Select condition: ", CONDITION_COUNT);
    strcpy(a.condition, CONDITIONS[c - 1]);

    assets[asset_count++] = a;
    printf("\n[Success] Asset added to register!\n");
}

void displayAssets(void) {
    if (asset_count == 0) {
        printf("\n[Info] No asset records found.\n");
        return;
    }

    printf("\n");
    printLine('=', 100);
    printf("%-8s %-20s %-17s %15s %-14s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine('-', 100);

    for (int i = 0; i < asset_count; i++) {
        printf("%-8.8s %-20.20s %-17.17s %15.2f %-14.14s %-10.10s\n",
               assets[i].id, assets[i].name, assets[i].type, assets[i].value,
               assets[i].department, assets[i].condition);
    }
    printLine('=', 100);
    printf("Total assets: %d\n", asset_count);
}

/* Search by exact ID (strcmp) or part of the asset name / type. */
void searchAsset(void) {
    if (asset_count == 0) {
        printf("\n[Info] Asset database is empty.\n");
        return;
    }

    char key[STR_LEN];
    int found = 0;

    readNonEmptyString("\nEnter Asset ID, name or type: ", key, sizeof key);

    for (int i = 0; i < asset_count; i++) {
        if (strcmp(assets[i].id, key) == 0 ||
            containsIgnoreCase(assets[i].name, key) ||
            containsIgnoreCase(assets[i].type, key)) {
            printAssetDetails(&assets[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\n[Info] No asset matching '%s' found.\n", key);
    } else {
        printf("\n%d asset(s) found.\n", found);
    }
}

void searchAssetByDepartment(void) {
    if (asset_count == 0) {
        printf("\n[Info] Asset database is empty.\n");
        return;
    }

    char dept[STR_LEN];
    int found = 0;

    readNonEmptyString("\nEnter Department: ", dept, sizeof dept);

    for (int i = 0; i < asset_count; i++) {
        if (containsIgnoreCase(assets[i].department, dept)) {
            printAssetDetails(&assets[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\n[Info] No assets found for department '%s'.\n", dept);
    } else {
        printf("\n%d asset(s) found.\n", found);
    }
}

void assetMenu(void) {
    int choice;
    do {
        printf("\n--- ASSET MANAGEMENT ---\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search by ID, Name or Type\n");
        printf("4. Search by Department\n");
        printf("5. Back to Main Menu\n");
        choice = readMenuChoice("Enter choice: ", 5);

        switch (choice) {
            case 1: addAsset();               break;
            case 2: displayAssets();          break;
            case 3: searchAsset();            break;
            case 4: searchAssetByDepartment(); break;
            case 5: break;
        }
    } while (choice != 5);
}
