#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clearScreen();

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

void pressEnterToContinue() {
    printf("Press Enter to return to the menu...");
    getchar(); 
    getchar();
}

Order* createOrder() {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    clearScreen();
    printf("Enter Order ID: ");
    scanf("%d", &newOrder->orderID);
    getchar(); 

    printf("Enter Food: ");
    fgets(newOrder->food, sizeof(newOrder->food), stdin);
    newOrder->food[strcspn(newOrder->food, "\n")] = '\0'; 

    printf("Enter Drink: ");
    fgets(newOrder->drink, sizeof(newOrder->drink), stdin);
    newOrder->drink[strcspn(newOrder->drink, "\n")] = '\0';

    printf("Enter Price: ");
    scanf("%f", &newOrder->price);
    printf("Enter Quantity: ");
    scanf("%d", &newOrder->quantity);

    newOrder->total = newOrder->price * newOrder->quantity;
    
    getchar(); 
    printf("Enter Type (regular/senior): ");
    fgets(newOrder->type, sizeof(newOrder->type), stdin);
    newOrder->type[strcspn(newOrder->type, "\n")] = '\0';

    for (int i = 0; newOrder->type[i]; i++) {
        newOrder->type[i] = tolower(newOrder->type[i]);
    }

    newOrder->next = NULL;
    return newOrder;
}

void addOrder() {
    Order* newOrder = createOrder();

    if (strcmp(newOrder->type, "regular") == 0) {
        if (regularHead == NULL) {
            regularHead = newOrder;
        } else {
            Order* temp = regularHead;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newOrder;
        }
    } else if (strcmp(newOrder->type, "senior") == 0) {
        newOrder->next = seniorHead;
        seniorHead = newOrder;
    } else {
        printf("Invalid type. Order not added.\n");
        free(newOrder);
    }
}

void viewOrders(int option) {
    Order* temp;

    if (option == 1) {
        temp = regularHead;
        printf("\n--- REGULAR ORDERS ---\n");
    } else if (option == 2) {
        temp = seniorHead;
        printf("\n--- SENIOR ORDERS ---\n");
    } else {
        printf("Invalid option.\n");
        return;
    }

    if (temp == NULL) {
        printf("No orders found.\n");
        pressEnterToContinue();
        return;
    }

    while (temp != NULL) {
        printf("\nOrder ID: %d\n", temp->orderID);
        printf("Food: %s\n", temp->food);
        printf("Drink: %s\n", temp->drink);
        printf("Price: %.2f\n", temp->price);
        printf("Quantity: %d\n", temp->quantity);
        printf("Total: %.2f\n", temp->total);
        printf("Type: %s\n", temp->type);
        temp = temp->next;
    }
    printf("\n");
    pressEnterToContinue();
}

int deleteOrder(Order** head, int orderID) {
    Order* temp = *head;
    Order* prev = NULL;

    while (temp != NULL && temp->orderID != orderID) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return 0;

    if (prev == NULL)
        *head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    return 1;
}

void payment() {
    int id;
    float amount;
    clearScreen();
    printf("Enter Order ID to pay: ");
    scanf("%d", &id);

    Order* temp = seniorHead;
    while (temp != NULL && temp->orderID != id)
        temp = temp->next;

    if (temp != NULL) {
        printf("Total Amount: %.2f\n", temp->total);
        printf("Enter Payment: ");
        scanf("%f", &amount);
        if (amount >= temp->total) {
            if (deleteOrder(&seniorHead, id))
                printf("Payment successful. Change: %.2f\n", amount - temp->total);
        } else {
            printf("Insufficient payment.\n");
        }
        pressEnterToContinue();
        return;
    }

    temp = regularHead;
    while (temp != NULL && temp->orderID != id)
        temp = temp->next;

    if (temp != NULL) {
        printf("Total Amount: %.2f\n", temp->total);
        printf("Enter Payment: ");
        scanf("%f", &amount);
        if (amount >= temp->total) {
            if (deleteOrder(&regularHead, id))
                printf("Payment successful. Change: %.2f\n", amount - temp->total);
        } else {
            printf("Insufficient payment.\n");
        }
        pressEnterToContinue();
        return;
    }

    printf("Order ID not found.\n");
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
void exitL(){
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
}

void menu() {
    int choice;
    do {
        system("cls || clear");
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
            case 1: addOrder(); break;
            case 2: viewOrders(1); break;
            case 3: viewOrders(2); break;
            case 4: payment(); break;
            case 5: exitL(); break;
            default: 
                printf("Invalid option.\n");
                pressEnterToContinue();
        }

    } while (choice != 5);
}

int main() {
    menu();
    freeOrders(regularHead);
    freeOrders(seniorHead);
    return 0;
}
void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}