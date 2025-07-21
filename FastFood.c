#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
Order* createOrder();
void exitL();
void menu();
void pressEnterToContinue();

Order* createOrder() {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    clearScreen();
    printf("--------------------------------------------------------------------\n");
    printf("|      Food:       Price:              Drinks:          Price       |\n");
    printf("|1. Calamares      ₱ 105               Coke             ₱ 30        |\n");
    printf("|2. DugoDugoan     ₱ 70                Ice Tea          ₱ 69        |\n");
    printf("|3. Kaldirita      ₱ 250               Blue Lemonade    ₱ 49        |\n");
    printf("|4. Chicken Manok  ₱ 160               Juice            ₱ 59        |\n");
    printf("|5. Atay-Atay      ₱ 120                                            |\n");
    printf("|6. Exit                                                            |\n");
    printf("--------------------------------------------------------------------\n");
    
    printf("Enter Order ID: ");
    scanf("%d", &newOrder->orderID);
    getchar(); 

    printf("Enter Food: ");
    fgets(newOrder->food, sizeof(newOrder->food), stdin);
    newOrder->food[strcspn(newOrder->food, "\n")] = '\0'; 

    printf("Enter Drink: ");
    fgets(newOrder->drink, sizeof(newOrder->drink), stdin);
    newOrder->drink[strcspn(newOrder->drink, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &newOrder->quantity);

    newOrder->price = 0; 
    newOrder->total = newOrder->price * newOrder->quantity;

    newOrder->next = NULL;

    printf("Order created successfully.\n");
    pressEnterToContinue();
    return newOrder; 
}

void pressEnterToContinue() {
    printf("Press Enter to continue...");
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
        printf("[4] Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                createOrder(); 
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
    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
