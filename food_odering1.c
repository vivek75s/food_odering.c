#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD 50
#define MAX_ORDER 50

// Structure for Food
struct Food
{
    int id;
    char name[50];
    float price;
};

// Structure for Order
struct Order
{
    int id;
    char name[50];
    float price;
    int quantity;
    float amount;
};

// Global variables
struct Food menu[MAX_FOOD] =
{
    {1, "Veg Biryani", 150},
    {2, "Chicken Biryani", 220},
    {3, "Pizza", 250},
    {4, "Burger", 120},
    {5, "Dosa", 80},
    {6, "Tea", 20},
    {7, "Coffee", 30},
    {8, "Cool Drink", 40}
};

struct Order order[MAX_ORDER];

int foodCount = 8;
int orderCount = 0;


// Function declarations
void showMenu();
void placeOrder();
void viewOrder();
void cancelOrder();
void generateBill();
void saveBill();
void addNewFood();
void deleteFood();


// Function to display food menu
void showMenu()
{
    int i;

    printf("\n============================================\n");
    printf("              FOOD MENU\n");
    printf("============================================\n");

    printf("%-5s %-20s %-10s\n", "ID", "Food Item", "Price");
    printf("--------------------------------------------\n");

    for(i = 0; i < foodCount; i++)
    {
        printf("%-5d %-20s Rs. %.2f\n",
               menu[i].id,
               menu[i].name,
               menu[i].price);
    }

    printf("============================================\n");
}


void placeOrder()
{
    int id;
    int quantity;
    int i;
    int found;
    char choice;

    do
    {
        if(orderCount >= MAX_ORDER)
        {
            printf("\nOrder limit reached!\n");
            return;
        }

        showMenu();

        printf("\nEnter Food ID: ");
        scanf("%d", &id);

        found = 0;

        for(i = 0; i < foodCount; i++)
        {
            if(menu[i].id == id)
            {
                found = 1;

                printf("Enter Quantity: ");
                scanf("%d", &quantity);

                if(quantity <= 0)
                {
                    printf("\nInvalid quantity!\n");
                    return;
                }

                order[orderCount].id = menu[i].id;

                strcpy(order[orderCount].name,
                       menu[i].name);

                order[orderCount].price = menu[i].price;

                order[orderCount].quantity = quantity;

                order[orderCount].amount =
                    menu[i].price * quantity;

                orderCount++;

                printf("\nItem added to order successfully!\n");

                break;
            }
        }

        if(found == 0)
        {
            printf("\nFood ID not found!\n");
        }

        printf("\nDo you want to order another item? (Y/N): ");
        scanf(" %c", &choice);

    } while(choice == 'Y' || choice == 'y');

    printf("\nOrder placed successfully!\n");
}


// Function to view order
void viewOrder()
{
    int i;
    float total = 0;

    if(orderCount == 0)
    {
        printf("\nNo orders available!\n");
        return;
    }

    printf("\n====================================================\n");
    printf("                    YOUR ORDER\n");
    printf("====================================================\n");

    printf("%-5s %-20s %-8s %-10s %-10s\n",
           "ID", "Food", "Qty", "Price", "Amount");

    printf("----------------------------------------------------\n");

    for(i = 0; i < orderCount; i++)
    {
        printf("%-5d %-20s %-8d Rs.%-8.2f Rs.%-8.2f\n",
               order[i].id,
               order[i].name,
               order[i].quantity,
               order[i].price,
               order[i].amount);

        total = total + order[i].amount;
    }

    printf("----------------------------------------------------\n");
    printf("Total Amount : Rs. %.2f\n", total);
    printf("====================================================\n");
}


// Function to cancel order
void cancelOrder()
{
	
    int id;
    int i, j;
    int found;
    char choice;

    if(orderCount == 0)
    {
        printf("\nNo orders available to cancel!\n");
        return;
    }

    do
    {
        viewOrder();

        printf("\nEnter Food ID to cancel: ");
        scanf("%d", &id);

        found = 0;

        for(i = 0; i < orderCount; i++)
        {
            if(order[i].id == id)
            {
                found = 1;

                // Shift remaining orders
                for(j = i; j < orderCount - 1; j++)
                {
                    order[j] = order[j + 1];
                }

                orderCount--;

                printf("\nOrder with Food ID %d cancelled successfully!\n", id);

                break;
            }
        }

        if(found == 0)
        {
            printf("\nFood ID not found in your order!\n");
        }

        if(orderCount > 0)
        {
            printf("\nDo you want to cancel another order? (Y/N): ");
            scanf(" %c", &choice);
        }
        else
        {
            printf("\nAll orders have been cancelled.\n");
            choice = 'N';
        }

    } while(choice == 'Y' || choice == 'y');
}

void cancelTotalOrder()
{
    char choice;

    if(orderCount == 0)
    {
        printf("\nNo orders available to cancel!\n");
        return;
    }

    printf("\nAre you sure you want to cancel the complete order? (Y/N): ");
    scanf(" %c", &choice);

    if(choice == 'Y' || choice == 'y')
    {
        orderCount = 0;

        printf("\n============================================\n");
        printf("       COMPLETE ORDER CANCELLED!\n");
        printf("============================================\n");
    }
    else
    {
        printf("\nOrder cancellation cancelled.\n");
    }
}


// Function to generate bill
void generateBill()
{
    int i;
    float subtotal = 0;
    float gst;
    float grandTotal;

    if(orderCount == 0)
    {
        printf("\nNo orders available!\n");
        return;
    }

    for(i = 0; i < orderCount; i++)
    {
        subtotal = subtotal + order[i].amount;
    }

    gst = subtotal * 0.05;

    grandTotal = subtotal + gst;

    printf("\n====================================================\n");
    printf("                  FOOD ORDER BILL\n");
    printf("====================================================\n");

    printf("%-20s %-8s %-10s %-10s\n",
           "Food", "Qty", "Price", "Amount");

    printf("----------------------------------------------------\n");

    for(i = 0; i < orderCount; i++)
    {
        printf("%-20s %-8d Rs.%-8.2f Rs.%-8.2f\n",
               order[i].name,
               order[i].quantity,
               order[i].price,
               order[i].amount);
    }

    printf("----------------------------------------------------\n");

    printf("Subtotal      : Rs. %.2f\n", subtotal);
    printf("GST (5%%)      : Rs. %.2f\n", gst);
    printf("Grand Total   : Rs. %.2f\n", grandTotal);

    printf("====================================================\n");
    printf("             Thank You! Visit Again.\n");
    printf("====================================================\n");
}


// Function to save bill
void saveBill()
{
    FILE *fp;
    int i;
    float subtotal = 0;
    float gst;
    float grandTotal;

    if(orderCount == 0)
    {
        printf("\nNo orders available to save!\n");
        return;
    }

    fp = fopen("bill.txt", "w");

    if(fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    for(i = 0; i < orderCount; i++)
    {
        subtotal = subtotal + order[i].amount;
    }

    gst = subtotal * 0.05;

    grandTotal = subtotal + gst;

    fprintf(fp, "============================================\n");
    fprintf(fp, "              FOOD ORDER BILL\n");
    fprintf(fp, "============================================\n");

    fprintf(fp, "%-20s %-8s %-10s %-10s\n",
            "Food", "Qty", "Price", "Amount");

    fprintf(fp, "--------------------------------------------\n");

    for(i = 0; i < orderCount; i++)
    {
        fprintf(fp, "%-20s %-8d Rs.%-8.2f Rs.%-8.2f\n",
                order[i].name,
                order[i].quantity,
                order[i].price,
                order[i].amount);
    }

    fprintf(fp, "--------------------------------------------\n");

    fprintf(fp, "Subtotal    : Rs. %.2f\n", subtotal);
    fprintf(fp, "GST (5%%)    : Rs. %.2f\n", gst);
    fprintf(fp, "Grand Total : Rs. %.2f\n", grandTotal);

    fprintf(fp, "============================================\n");
    fprintf(fp, "        Thank You! Visit Again.\n");
    fprintf(fp, "============================================\n");

    fclose(fp);

    printf("\nBill saved successfully in bill.txt\n");
}


// Function to add new food
void addNewFood()
{
    if(foodCount >= MAX_FOOD)
    {
        printf("\nFood menu is full!\n");
        return;
    }

    menu[foodCount].id = foodCount + 1;

    printf("\nEnter New Food Name: ");
    scanf(" %[^\n]", menu[foodCount].name);

    printf("Enter Food Price: ");
    scanf("%f", &menu[foodCount].price);

    foodCount++;

    printf("\nNew food item added successfully!\n");
}



// Main function
int main()
{
    int choice;

    do
    {
        printf("\n\n============================================\n");
        printf("        FOOD ORDERING MANAGEMENT SYSTEM\n");
        printf("============================================\n");

        printf("1. Show Menu\n");
        printf("2. Place Order\n");
        printf("3. View Order\n");
        printf("4. Cancel Order\n");
	printf("5. Cancel total order\n");
        printf("6. Generate Bill\n");
        printf("7. Save Bill\n");
        printf("8. Add New Food\n");
        printf("9. Exit\n");

        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                showMenu();
                break;

            case 2:
                placeOrder();
                break;

            case 3:
                viewOrder();
                break;

            case 4:
                cancelOrder();
                break;
	    case 5:
		cancelTotalOrder();

            case 6:
                generateBill();
                break;

            case 7:
                saveBill();
                break;

            case 8:
                addNewFood();
                break;

            case 9:
                printf("\nThank You! Program Exited.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 9);

    return 0;
}
