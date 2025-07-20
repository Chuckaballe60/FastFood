#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Order {
    int orderID;
    char food[30];
    char drink[30];
    float price;
    int quantity;
    float total;
    char type[10];
    struct Order* next;
} Order;

Order* regularHead = NULL;
Order* seniorHead = NULL;

void clearScreen();
void pressEnterToContinue();
void exitL();
void menu();
void payment(); 
void freeOrders(Order* head);

void clearScreen() {
    system("cls || clear");
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    getchar(); 
    getchar(); 
}

void exitL() {
    clearScreen();
    printf("    .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .-----------------. .----------------. \n");
    printf("   | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
    printf("   | |  _________   | || |  ____  ____  | || |     _____    | || |  _________   | || |     _____    | || | ____  _____  | || |    ______    | |\n");
    printf("   | | |_   ___  |  | || | |_  _||_  _| | || |    |_   _|   | || | |  _   _  |  | || |    |_   _|   | || ||_   \\|_   _| | || |  .' ___  |   | |\n");
    printf("   | |   | |_  \\_|  | || |   \\ \\  / /   | || |      | |     | || | |_/ | | \\_|  | || |      | |     | || |  |   \\ | |   | || | / .'   \\_|   | |\n");
    printf("   | |   |  _|  _   | || |    > `' <    | || |      | |     | || |     | |      | || |      | |     | || |  | |\\ \\| |   | || | | |    ____  | |\n");
    printf("   | |  _| |___/ |  | || |  _/ /'`\\ \\_  | || |     _| |_    | || |    _| |_     | || |     _| |_    | || | _| |\\_   |_  | || | \\ `.___]  _| | |\n");
    printf("   | | |_________|  | || | |____||____| | || |    |_____|   | || |   |_____|    | || |    |_____|   | || ||_____|\____| | || |  `._____.'   | |\n");
    printf("   | |              | || |              | || |              | || |              | || |              | || |              | || |              | |\n");
    printf("   | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
    printf("   '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  \n");

    pressEnterToContinue();
}

void menu() {
    int choice;
    do {
        clearScreen();
        printf(" ______        _    ______              _   _   _       _ \n");
        printf("|  ___|      | |   |  ___|            | | | | | |     | |\n");
        printf("| |_ __ _ ___| |_  | |_ ___   ___   __| | | |_| |_   _| |__\n");
        printf("|  _/ _` / __| __| |  _/ _ \\ / _ \\ / _` | |  _  | | | | '_ \\ \n");
        printf("| || (_| \\__ \\ |_  | || (_) | (_) | (_| | | | | | |_| | |_) |\n");
        printf("\\_| \\__,_|___/\\__| \\_| \\___/ \\___/ \\__,_| \\_| |_/\\__,_|_.__/\n");

        printf("\n=== FAST FOOD HUB ===\n");
        printf("[1] Add Order\n");
        printf("[2] View Regular Orders\n");
        printf("[3] View Senior Orders\n");
        printf("[4] Payment\n");
        printf("[5] Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                pressEnterToContinue();
                break;
            case 2:
                pressEnterToContinue();
                break;
            case 3:
                pressEnterToContinue();
                break;
            case 4:
                payment();
                break;
            case 5:
                exitL();
                break;
            default:
                printf("Invalid option.\n");
                pressEnterToContinue();
        }

    } while (choice != 5);
}

void payment() {
    pressEnterToContinue();
}

void freeOrders(Order* head) {
    Order* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    menu();
    freeOrders(regularHead);
    freeOrders(seniorHead);
    return 0;
}
