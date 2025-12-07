#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "expenses.txt"

typedef struct {
    int id;
    float amount;
    char category[30];
    char date[15];
} Expense;

/* Function declarations */
void addExpense();
void viewExpenses();
void searchExpense();
void editExpense();
void deleteExpense();
void deleteAllExpenses();

int main() {
    int choice;

    while (1) {
        printf("\n===== Expense Tracker =====\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. Search Expense by ID\n");
        printf("4. Edit Expense\n");
        printf("5. Delete Expense\n");
        printf("6. Delete All Expenses\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                searchExpense();
                break;
            case 4:
                editExpense();
                break;
            case 5:
                deleteExpense();
                break;
            case 6:
                deleteAllExpenses();
                break;
            case 7:
    expenseSummary();
    break;
case 8:
    printf("Thank you for using Expense Tracker\n");
    exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

/* Add Expense */
void addExpense() {
    Expense e;
    FILE *fp = fopen(FILE_NAME, "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &e.id);
    printf("Enter Amount: ");
    scanf(" %f", &e.amount);
    printf("Enter Category: ");
    scanf("%s", e.category);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf(" %s", e.date);

    fprintf(fp, "%d %.2f %s %s\n", e.id, e.amount, e.category, e.date);
    fclose(fp);

    printf("Expense added successfully!\n");
}

/* View All Expenses */
void viewExpenses() {
    Expense e;
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\nID\tAmount\tCategory\tDate\n");
    printf("-------------------------------------\n");

    while (fscanf(fp, "%d %f %s %s", &e.id, &e.amount, e.category, e.date) != EOF) {
        printf("%d\t%.2f\t%s\t\t%s\n", e.id, e.amount, e.category, e.date);
    }

    fclose(fp);
}

/* Search Expense */
void searchExpense() {
    Expense e;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %f %s %s", &e.id, &e.amount, e.category, e.date) != EOF) {
        if (e.id == id) {
            printf("ID: %d\nAmount: %.2f\nCategory: %s\nDate: %s\n",
                   e.id, e.amount, e.category, e.date);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Expense not found!\n");

    fclose(fp);
}

/* Edit Expense */
void editExpense() {
    Expense e;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID to edit: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %f %s %s", &e.id, &e.amount, e.category, e.date) != EOF) {
        if (e.id == id) {
            printf("Enter new Amount: ");
            scanf("%f", &e.amount);
            printf("Enter new Category: ");
            scanf("%s", e.category);
            printf("Enter new Date: ");
            scanf("%s", e.date);
            found = 1;
        }
        fprintf(temp, "%d %.2f %s %s\n", e.id, e.amount, e.category, e.date);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Expense updated successfully!\n");
    else
        printf("Expense not found!\n");
}

/* Delete Expense */
void deleteExpense() {
    Expense e;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %f %s %s", &e.id, &e.amount, e.category, e.date) != EOF) {
        if (e.id == id) {
            found = 1;
        } else {
            fprintf(temp, "%d %.2f %s %s\n", e.id, e.amount, e.category, e.date);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Expense deleted successfully!\n");
    else
        printf("Expense not found!\n");
}

/* Delete All Expenses */
void deleteAllExpenses() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp != NULL) {
        fclose(fp);
        printf("All expenses deleted!\n");
    }
}
void expenseSummary() {
    Expense e;
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    float total = 0;
    char categories[50][30];
    float catTotal[50];
    int catCount = 0;

    while (fscanf(fp, "%d %f %s %s",
                  &e.id, &e.amount, e.category, e.date) != EOF) {

        total += e.amount;

        int found = 0;
        for (int i = 0; i < catCount; i++) {
            if (strcmp(categories[i], e.category) == 0) {
                catTotal[i] += e.amount;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(categories[catCount], e.category);
            catTotal[catCount] = e.amount;
            catCount++;
        }
    }

    fclose(fp);

    printf("\n===== Expense Summary =====\n");
    printf("Total Expense: %.2f\n\n", total);
    printf("Category-wise Summary:\n");

    for (int i = 0; i < catCount; i++) {
        printf("%s : %.2f\n", categories[i], catTotal[i]);
    }
}

