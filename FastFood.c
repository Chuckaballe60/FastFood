
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Order {
    int orderID;
    char food[30];
    char drink[30];
    float foodPrice;
    float drinkPrice;
    int foodQuantity;
    int drinkQuantity;
    float total;
    char type[10];
    struct Order* next;
} Order;

Order* regularHead = NULL;
Order* seniorHead = NULL;

void clearScreen();
void pressEnterToContinue();
Order* createOrder();
void addOrder();
void viewOrders(int option);
int deleteOrder(Order** head, int orderID);
void payment();
void freeOrders(Order* head);
void exitL();
void menu();

void viewOrderOptions() {
    int subChoice;
    do {
        printf("\n[1] View Regular Orders\n");
        printf("[2] View Senior Orders\n");
        printf("[3] Return to Menu\n");
        printf("Enter choice: ");
        scanf("%d", &subChoice);

        switch (subChoice) {
            case 1: viewOrders(1); break;
            case 2: viewOrders(2); break;
            case 3: break;
            default: 
                printf("Invalid option. Please try again.\n");
                pressEnterToContinue();
        }
    } while (subChoice != 3);
}

void pressEnterToContinue() {
    printf("Press Enter to return to the menu...");
    getchar(); 
    getchar();
}

float getFoodPrice(int choice) {
    switch (choice) {
        case 1: return 105; 
        case 2: return 70;  
        case 3: return 250; 
        case 4: return 160; 
        case 5: return 120; 
    }
}

float getDrinkPrice(int choice) {
    switch (choice) {
        case 1: return 30;  
        case 2: return 69;  
        case 3: return 49;  
        case 4: return 59;  
        default: return -1;  
    }
}

Order* createOrder() {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    clearScreen();
    printf("--------------------------------------------------------------------\n");
    printf("|      Food:       Price:              Drinks:          Price       |\n");
    printf("|1. Calamares      ₱ 105               1. Coke            ₱ 30      |\n");
    printf("|2. DugoDugoan     ₱ 70                2. Ice Tea        ₱ 69      |\n");
    printf("|3. Kaldirita      ₱ 250               3. Blue Lemonade  ₱ 49      |\n");
    printf("|4. Chicken Manok  ₱ 160               4. Juice          ₱ 59      |\n");
    printf("|5. Atay-Atay      ₱ 120                                            |\n");
    printf("|6. Exit                                                            |\n");
    printf("--------------------------------------------------------------------\n");
    
    printf("Enter Order ID: ");
    scanf("%d", &newOrder->orderID);
    getchar(); 

    int foodChoice, drinkChoice;

    do {
        printf("Select Food (1-5): ");
        scanf("%d", &foodChoice);
        newOrder->foodPrice = getFoodPrice(foodChoice);
        if (newOrder->foodPrice < 0) {
            printf("Invalid food item. Please try again.\n");
        } else {
            printf("Enter Food Price: ");
            scanf("%f", &newOrder->foodPrice);
        }
    } while (newOrder->foodPrice < 0);
    
    printf("Enter Food Quantity: ");
    scanf("%d", &newOrder->foodQuantity);
    newOrder->total = newOrder->foodPrice * newOrder->foodQuantity;

    do {
        printf("Select Drink (1-4): ");
        scanf("%d", &drinkChoice);
        newOrder->drinkPrice = getDrinkPrice(drinkChoice);
        if (newOrder->drinkPrice < 0) {
            printf("Invalid drink item. Please try again.\n");
        } else {
            printf("Enter Drink Price: ");
            scanf("%f", &newOrder->drinkPrice);
        }
    } while (newOrder->drinkPrice < 0);

    printf("Enter Drink Quantity: ");
    scanf("%d", &newOrder->drinkQuantity);
    newOrder->total += newOrder->drinkPrice * newOrder->drinkQuantity;

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
    if (newOrder == NULL) return; 

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
        return;
    }

    printf("Order Added.\n");
    pressEnterToContinue();
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
        printf("Food Price: %.2f\n", temp->foodPrice);
        printf("Food Quantity: %d\n", temp->foodQuantity);
        printf("Drink: %s\n", temp->drink);
        printf("Drink Price: %.2f\n", temp->drinkPrice);
        printf("Drink Quantity: %d\n", temp->drinkQuantity);
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
    clearScreen();
    printf("Enter Order ID to pay: ");
    scanf("%d", &id);

    Order* temp = seniorHead;
    while (temp != NULL && temp->orderID != id)
        temp = temp->next;

    if (temp != NULL) {
        printf("Total Amount: %.2f\n", temp->total);
        printf("Order paid and removed.\n");
        deleteOrder(&seniorHead, id);
        pressEnterToContinue();
        return;
    }

    temp = regularHead;
    while (temp != NULL && temp->orderID != id)
        temp = temp->next;

    if (temp != NULL) {
        printf("Total Amount: %.2f\n", temp->total);
        printf("Order paid and removed.\n");
        deleteOrder(&regularHead, id);
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
        printf("[2] View Orders\n");
        printf("[3] Payment\n");
        printf("[4] Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                addOrder(); 
                break;
            case 2: 
                viewOrderOptions(); 
                break; 
            case 3: 
                payment(); 
                break;
            case 4: 
                exitL(); 
                break;
            default: 
                printf("Invalid option.\n");
                pressEnterToContinue();
        }

    } while (choice != 4);
}

int main() {
    menu();
    freeOrders(regularHead);
    freeOrders(seniorHead);
    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}