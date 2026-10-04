#include <stdio.h>
#include <string.h>

// 1. MACRO DEFINITIONS 
#define MAX_ASSETS 50
#define STR_LEN 50

// 2. FUNCTION PROTOTYPES (Blueprint declarations)
void manageAssets(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int *assetCount);
void addAsset(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int *assetCount);
void displayAssets(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int assetCount);
void searchAsset(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int assetCount);

// 3. MAIN RUNNER (Fixes the "undefined reference to main" error)
int main() {
    // Allocation of parallel storage arrays as required by the course syllabus
    int assetIds[MAX_ASSETS];
    char assetNames[MAX_ASSETS][STR_LEN];
    char assetTypes[MAX_ASSETS][STR_LEN];
    float assetValues[MAX_ASSETS];
    char assetDepts[MAX_ASSETS][STR_LEN];
    char assetConditions[MAX_ASSETS][STR_LEN];
    int currentAssetCount = 0;

    printf("--- Standalone Asset Module System Loading ---\n");
    
    // Launches your interactive menu workflow dashboard
    manageAssets(assetIds, assetNames, assetTypes, assetValues, assetDepts, assetConditions, &currentAssetCount);
    
    return 0;
}

// 4. SUB-MENU INTERFACE DRIVER
void manageAssets(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int *assetCount) {
    int choice;
    do {
        printf("\n========================================\n");
        printf("            ASSET MANAGEMENT            \n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset Information\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid option. Please enter a number.\n");
            while (getchar() != '\n'); // Clear stream buffer corruption
            continue;
        }
        getchar(); // Consume trailing newline character

        switch (choice) {
            case 1:
                addAsset(ids, names, types, values, depts, conds, assetCount);
                break;
            case 2:
                displayAssets(ids, names, types, values, depts, conds, *assetCount);
                break;
            case 3:
                searchAsset(ids, names, types, values, depts, conds, *assetCount);
                break;
            case 4:
                printf("Exiting Asset Sub-System Menu...\n");
                break;
            default:
                printf("Invalid selection! Please enter an integer from 1 to 4.\n");
        }
    } while (choice != 4);
}

// 5. DATA INTAKE & VALIDATION
void addAsset(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int *assetCount) {
    if (*assetCount >= MAX_ASSETS) {
        printf("Registry Error: Maximum asset storage limit reached!\n");
        return;
    }

    int idx = *assetCount;
    printf("\n--- Register New Municipal Asset ---\n");

    // Positive Asset ID Input Check
    printf("Enter Asset ID (Positive Integer): ");
    while (scanf("%d", &ids[idx]) != 1 || ids[idx] <= 0) {
        printf("Validation Error: ID must be a positive integer. Re-enter: ");
        while (getchar() != '\n'); 
    }
    getchar();

    // Asset Name Empty Validation Check
    printf("Enter Asset Name: ");
    fgets(names[idx], STR_LEN, stdin);
    names[idx][strcspn(names[idx], "\n")] = 0; // Strip trailing newline character
    if (strlen(names[idx]) == 0) {
        strcpy(names[idx], "Default Asset"); // Fallback text population
    }

    // Required Municipal Asset Category Type Matrix Selections
    int typeSelect;
    printf("Select Asset Type:\n 1. Vehicles\n 2. Computers\n 3. Buildings\n 4. Equipment\n 5. Office furniture\nChoice (1-5): ");
    while (scanf("%d", &typeSelect) != 1 || typeSelect < 1 || typeSelect > 5) {
        printf("Validation Error: Choice must be between 1 and 5. Re-enter: ");
        while (getchar() != '\n');
    }
    getchar();

    if (typeSelect == 1) strcpy(types[idx], "Vehicles");
    else if (typeSelect == 2) strcpy(types[idx], "Computers");
    else if (typeSelect == 3) strcpy(types[idx], "Buildings");
    else if (typeSelect == 4) strcpy(types[idx], "Equipment");
    else strcpy(types[idx], "Office furniture");

    // Purchase Value Negative Input Check
    printf("Enter Purchase Value (N$): ");
    while (scanf("%f", &values[idx]) != 1 || values[idx] < 0) {
        printf("Validation Error: Negative values are not permitted. Re-enter: ");
        while (getchar() != '\n');
    }
    getchar();

    // Department Field Collection
    printf("Enter Managing Department: ");
    fgets(depts[idx], STR_LEN, stdin);
    depts[idx][strcspn(depts[idx], "\n")] = 0;

    // Condition Field Collection
    printf("Enter Asset Condition Status: ");
    fgets(conds[idx], STR_LEN, stdin);
    conds[idx][strcspn(conds[idx], "\n")] = 0;

    (*assetCount)++;
    printf("Success: Municipal asset record stored successfully!\n");
}

// 6. TABLE DISPLAY COMPONENT
void displayAssets(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int assetCount) {
    if (assetCount == 0) {
        printf("\nThe municipal asset registry database is empty.\n");
        return;
    }

    printf("\n=================================================================================\n");
    printf("%-10s %-18s %-18s %-12s %-12s %-10s\n", "Asset ID", "Asset Name", "Asset Type", "Value (N$)", "Department", "Condition");
    printf("=================================================================================\n");
    for (int i = 0; i < assetCount; i++) {
        printf("%-10d %-18s %-18s %-12.2f %-12s %-10s\n", ids[i], names[i], types[i], values[i], depts[i], conds[i]);
    }
    printf("=================================================================================\n");
}

// 7. DATABASE RETRIEVAL COMPONENT (SEARCH)
void searchAsset(int ids[], char names[][STR_LEN], char types[][STR_LEN], float values[], char depts[][STR_LEN], char conds[][STR_LEN], int assetCount) {
    if (assetCount == 0) {
        printf("\nSearch structural warning: No asset records available to scan.\n");
        return;
    }

    int searchId;
    printf("\nEnter Asset ID to locate: ");
    while (scanf("%d", &searchId) != 1) {
        printf("Validation Error: Enter a valid numerical ID parameter: ");
        while (getchar() != '\n');
    }
    getchar();

    for (int i = 0; i < assetCount; i++) {
        if (ids[i] == searchId) {
            printf("\n--- Asset Record Found ---\n");
            printf("Asset ID:       %d\n", ids[i]);
            printf("Asset Name:     %s\n", names[i]);
            printf("Asset Type:     %s\n", types[i]);
            printf("Purchase Value: N$%.2f\n", values[i]);
            printf("Department:     %s\n", depts[i]);
            printf("Condition:      %s\n", conds[i]);
            printf("--------------------------\n");
            return; // Terminate function as record match has been found
        }
    }
    printf("\nSearch Complete: Asset ID %d was not found inside this system.\n", searchId);
}
