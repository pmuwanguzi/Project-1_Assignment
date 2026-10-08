#include <stdio.h>

/* Discard any leftover characters on the current input line */
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    double balance = 0.0;      /* account balance in RWF               */
    double amount;             /* amount entered for a transaction     */
    int choice;                /* menu option selected by the agent    */
    int deposit_count = 0;     /* number of successful deposits        */
    int withdrawal_count = 0;  /* number of successful withdrawals     */
    int failed_count = 0;      /* number of rejected transactions      */

    while (1) /* main loop: runs until the agent selects Exit */
    {
        printf("\n===== MOBILE MONEY TRANSACTION SYSTEM =====\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Check Balance\n");
        printf("4. Transaction Summary\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        /* Validate that the choice is a number */
        if (scanf("%d", &choice) != 1)
        {
            if (feof(stdin)) /* no more input available: stop safely */
            {
                printf("\nNo more input. System terminated.\n");
                break;
            }
            clear_input_buffer();
            printf("Invalid input: please enter a number from 1 to 5.\n");
            continue; /* back to the menu */
        }
        clear_input_buffer();

        /* Validate that the choice is within the menu range */
        if (choice < 1 || choice > 5)
        {
            printf("Invalid choice: %d is not a menu option. Please select 1-5.\n", choice);
            continue; /* back to the menu */
        }

        /* Exit: break terminates the while loop */
        if (choice == 5)
        {
            printf("System terminated.\n");
            break;
        }

        switch (choice)
        {
        case 1: /* Deposit */
            printf("Enter deposit amount: ");
            if (scanf("%lf", &amount) != 1)
            {
                clear_input_buffer();
                printf("Transaction rejected: Amount must be a number.\n");
                failed_count++;
                continue;
            }
            clear_input_buffer();

            if (amount <= 0)
            {
                printf("Transaction rejected: Deposit amount must be greater than zero.\n");
                failed_count++;
                continue;
            }

            balance += amount;
            deposit_count++;
            printf("Deposit successful.\n");
            printf("Current balance: %.2f RWF\n", balance);
            break; /* leave the switch */

        case 2: /* Withdrawal */
            printf("Enter withdrawal amount: ");
            if (scanf("%lf", &amount) != 1)
            {
                clear_input_buffer();
                printf("Transaction rejected: Amount must be a number.\n");
                failed_count++;
                continue;
            }
            clear_input_buffer();

            if (amount <= 0)
            {
                printf("Transaction rejected: Withdrawal amount must be greater than zero.\n");
                failed_count++;
                continue;
            }
            else if (amount > balance)
            {
                printf("Transaction rejected: Insufficient balance.\n");
                printf("Available balance: %.2f RWF\n", balance);
                failed_count++;
                continue;
            }

            balance -= amount;
            withdrawal_count++;
            printf("Withdrawal successful.\n");
            printf("Current balance: %.2f RWF\n", balance);
            break;

        case 3: /* Balance inquiry */
            printf("Current balance: %.2f RWF\n", balance);
            break;

        case 4: /* Transaction summary */
            printf("----- TRANSACTION SUMMARY -----\n");
            printf("Successful deposits:    %d\n", deposit_count);
            printf("Successful withdrawals: %d\n", withdrawal_count);
            printf("Rejected transactions:  %d\n", failed_count);
            printf("Current balance:        %.2f RWF\n", balance);
            break;
        }
    }

    return 0;
}
