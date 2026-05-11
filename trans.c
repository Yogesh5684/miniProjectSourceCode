/*
=====================================================================
                ADVANCED BANK MANAGEMENT SYSTEM
=====================================================================

Developed Using:
- C Programming
- Structures
- File Handling
- Random Access Files
- Functions
- Binary File Operations

Features:
1. Create Account
2. View All Accounts
3. Search Account
4. Deposit Money
5. Withdraw Money
6. Transfer Money
7. Update Account Details
8. Delete Account
9. Generate Transaction Report
10. Exit

=====================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Definition
struct BankAccount
{
    int accountNumber;
    char firstName[30];
    char lastName[30];
    char gender[10];
    char phone[15];
    char address[50];
    double balance;
};

// Function Prototypes
void initializeFile();
void createAccount(FILE *fp);
void displayAccounts(FILE *fp);
void searchAccount(FILE *fp);
void depositMoney(FILE *fp);
void withdrawMoney(FILE *fp);
void transferMoney(FILE *fp);
void updateAccount(FILE *fp);
void deleteAccount(FILE *fp);
void generateReport(FILE *fp);
int menu();

// Main Function
int main()
{
    FILE *fp;

    initializeFile();

    fp = fopen("bankSystem.dat", "rb+");

    if (fp == NULL)
    {
        printf("Error Opening File\n");
        exit(1);
    }

    int choice;

    while ((choice = menu()) != 10)
    {
        switch (choice)
        {
        case 1:
            createAccount(fp);
            break;

        case 2:
            displayAccounts(fp);
            break;

        case 3:
            searchAccount(fp);
            break;

        case 4:
            depositMoney(fp);
            break;

        case 5:
            withdrawMoney(fp);
            break;

        case 6:
            transferMoney(fp);
            break;

        case 7:
            updateAccount(fp);
            break;

        case 8:
            deleteAccount(fp);
            break;

        case 9:
            generateReport(fp);
            break;

        default:
            printf("Invalid Choice\n");
        }
    }

    fclose(fp);

    printf("\nThank You For Using Bank Management System\n");

    return 0;
}

// Initialize Binary File
void initializeFile()
{
    FILE *fp;

    struct BankAccount blankAccount =
    {
        0, "", "", "", "", "", 0.0
    };

    fp = fopen("bankSystem.dat", "rb");

    if (fp == NULL)
    {
        fp = fopen("bankSystem.dat", "wb");

        for (int i = 0; i < 100; i++)
        {
            fwrite(&blankAccount,
                   sizeof(struct BankAccount),
                   1,
                   fp);
        }

        printf("Database File Created Successfully\n");
    }

    fclose(fp);
}

// Menu Function
int menu()
{
    int choice;

    printf("\n");
    printf("====================================================\n");
    printf("           BANK MANAGEMENT SYSTEM\n");
    printf("====================================================\n");
    printf("1. Create New Account\n");
    printf("2. Display All Accounts\n");
    printf("3. Search Account\n");
    printf("4. Deposit Money\n");
    printf("5. Withdraw Money\n");
    printf("6. Transfer Money\n");
    printf("7. Update Account\n");
    printf("8. Delete Account\n");
    printf("9. Generate Report\n");
    printf("10. Exit\n");
    printf("====================================================\n");
    printf("Enter Your Choice: ");

    scanf("%d", &choice);

    return choice;
}

// Create Account
void createAccount(FILE *fp)
{
    struct BankAccount account =
    {
        0, "", "", "", "", "", 0.0
    };

    int accNo;

    printf("\nEnter Account Number (1-100): ");
    scanf("%d", &accNo);

    fseek(fp,
          (accNo - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&account,
          sizeof(struct BankAccount),
          1,
          fp);

    if (account.accountNumber != 0)
    {
        printf("Account Already Exists\n");
    }
    else
    {
        account.accountNumber = accNo;

        printf("Enter First Name: ");
        scanf("%s", account.firstName);

        printf("Enter Last Name: ");
        scanf("%s", account.lastName);

        printf("Enter Gender: ");
        scanf("%s", account.gender);

        printf("Enter Phone Number: ");
        scanf("%s", account.phone);

        printf("Enter Address: ");
        scanf(" %[^\n]", account.address);

        printf("Enter Initial Balance: ");
        scanf("%lf", &account.balance);

        fseek(fp,
              (accNo - 1) * sizeof(struct BankAccount),
              SEEK_SET);

        fwrite(&account,
               sizeof(struct BankAccount),
               1,
               fp);

        printf("\nAccount Created Successfully\n");
    }
}

// Display All Accounts
void displayAccounts(FILE *fp)
{
    struct BankAccount account;

    rewind(fp);

    printf("\n");
    printf("=================================================================================================\n");

    printf("%-8s%-15s%-15s%-10s%-15s%-20s%-10s\n",
           "AccNo",
           "FirstName",
           "LastName",
           "Gender",
           "Phone",
           "Address",
           "Balance");

    printf("=================================================================================================\n");

    while (fread(&account,
                 sizeof(struct BankAccount),
                 1,
                 fp))
    {
        if (account.accountNumber != 0)
        {
            printf("%-8d%-15s%-15s%-10s%-15s%-20s%-10.2lf\n",
                   account.accountNumber,
                   account.firstName,
                   account.lastName,
                   account.gender,
                   account.phone,
                   account.address,
                   account.balance);
        }
    }
}

// Search Account
void searchAccount(FILE *fp)
{
    struct BankAccount account;

    int accNo;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    fseek(fp,
          (accNo - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&account,
          sizeof(struct BankAccount),
          1,
          fp);

    if (account.accountNumber == 0)
    {
        printf("Account Not Found\n");
    }
    else
    {
        printf("\n========== ACCOUNT DETAILS ==========\n");

        printf("Account Number : %d\n",
               account.accountNumber);

        printf("First Name     : %s\n",
               account.firstName);

        printf("Last Name      : %s\n",
               account.lastName);

        printf("Gender         : %s\n",
               account.gender);

        printf("Phone Number   : %s\n",
               account.phone);

        printf("Address        : %s\n",
               account.address);

        printf("Balance        : %.2lf\n",
               account.balance);
    }
}

// Deposit Money
void depositMoney(FILE *fp)
{
    struct BankAccount account;

    int accNo;
    double amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    fseek(fp,
          (accNo - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&account,
          sizeof(struct BankAccount),
          1,
          fp);

    if (account.accountNumber == 0)
    {
        printf("Account Not Found\n");
    }
    else
    {
        printf("Current Balance: %.2lf\n",
               account.balance);

        printf("Enter Deposit Amount: ");
        scanf("%lf", &amount);

        account.balance += amount;

        fseek(fp,
              -sizeof(struct BankAccount),
              SEEK_CUR);

        fwrite(&account,
               sizeof(struct BankAccount),
               1,
               fp);

        printf("Money Deposited Successfully\n");
        printf("Updated Balance: %.2lf\n",
               account.balance);
    }
}

// Withdraw Money
void withdrawMoney(FILE *fp)
{
    struct BankAccount account;

    int accNo;
    double amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    fseek(fp,
          (accNo - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&account,
          sizeof(struct BankAccount),
          1,
          fp);

    if (account.accountNumber == 0)
    {
        printf("Account Not Found\n");
    }
    else
    {
        printf("Current Balance: %.2lf\n",
               account.balance);

        printf("Enter Withdraw Amount: ");
        scanf("%lf", &amount);

        if (amount > account.balance)
        {
            printf("Insufficient Balance\n");
        }
        else
        {
            account.balance -= amount;

            fseek(fp,
                  -sizeof(struct BankAccount),
                  SEEK_CUR);

            fwrite(&account,
                   sizeof(struct BankAccount),
                   1,
                   fp);

            printf("Withdrawal Successful\n");
            printf("Remaining Balance: %.2lf\n",
                   account.balance);
        }
    }
}

// Transfer Money
void transferMoney(FILE *fp)
{
    struct BankAccount sender;
    struct BankAccount receiver;

    int senderAcc;
    int receiverAcc;

    double amount;

    printf("Enter Sender Account Number: ");
    scanf("%d", &senderAcc);

    printf("Enter Receiver Account Number: ");
    scanf("%d", &receiverAcc);

    printf("Enter Transfer Amount: ");
    scanf("%lf", &amount);

    // Sender
    fseek(fp,
          (senderAcc - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&sender,
          sizeof(struct BankAccount),
          1,
          fp);

    // Receiver
    fseek(fp,
          (receiverAcc - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&receiver,
          sizeof(struct BankAccount),
          1,
          fp);

    if (sender.accountNumber == 0 ||
        receiver.accountNumber == 0)
    {
        printf("Invalid Accounts\n");
    }
    else if (amount > sender.balance)
    {
        printf("Insufficient Balance\n");
    }
    else
    {
        sender.balance -= amount;
        receiver.balance += amount;

        // Update Sender
        fseek(fp,
              (senderAcc - 1) * sizeof(struct BankAccount),
              SEEK_SET);

        fwrite(&sender,
               sizeof(struct BankAccount),
               1,
               fp);

        // Update Receiver
        fseek(fp,
              (receiverAcc - 1) * sizeof(struct BankAccount),
              SEEK_SET);

        fwrite(&receiver,
               sizeof(struct BankAccount),
               1,
               fp);

        printf("Money Transfer Successful\n");
    }
}

// Update Account
void updateAccount(FILE *fp)
{
    struct BankAccount account;

    int accNo;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    fseek(fp,
          (accNo - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&account,
          sizeof(struct BankAccount),
          1,
          fp);

    if (account.accountNumber == 0)
    {
        printf("Account Not Found\n");
    }
    else
    {
        printf("Enter New Phone Number: ");
        scanf("%s", account.phone);

        printf("Enter New Address: ");
        scanf(" %[^\n]", account.address);

        fseek(fp,
              -sizeof(struct BankAccount),
              SEEK_CUR);

        fwrite(&account,
               sizeof(struct BankAccount),
               1,
               fp);

        printf("Account Updated Successfully\n");
    }
}

// Delete Account
void deleteAccount(FILE *fp)
{
    struct BankAccount account;

    struct BankAccount blankAccount =
    {
        0, "", "", "", "", "", 0.0
    };

    int accNo;

    printf("Enter Account Number To Delete: ");
    scanf("%d", &accNo);

    fseek(fp,
          (accNo - 1) * sizeof(struct BankAccount),
          SEEK_SET);

    fread(&account,
          sizeof(struct BankAccount),
          1,
          fp);

    if (account.accountNumber == 0)
    {
        printf("Account Not Found\n");
    }
    else
    {
        fseek(fp,
              (accNo - 1) * sizeof(struct BankAccount),
              SEEK_SET);

        fwrite(&blankAccount,
               sizeof(struct BankAccount),
               1,
               fp);

        printf("Account Deleted Successfully\n");
    }
}

// Generate Report
void generateReport(FILE *fp)
{
    FILE *report;

    struct BankAccount account;

    report = fopen("BankReport.txt", "w");

    if (report == NULL)
    {
        printf("Unable To Create Report\n");
        return;
    }

    rewind(fp);

    fprintf(report,
            "===============================================================\n");

    fprintf(report,
            "%-8s%-15s%-15s%-15s%-10s\n",
            "AccNo",
            "FirstName",
            "LastName",
            "Phone",
            "Balance");

    fprintf(report,
            "===============================================================\n");

    while (fread(&account,
                 sizeof(struct BankAccount),
                 1,
                 fp))
    {
        if (account.accountNumber != 0)
        {
            fprintf(report,
                    "%-8d%-15s%-15s%-15s%-10.2lf\n",
                    account.accountNumber,
                    account.firstName,
                    account.lastName,
                    account.phone,
                    account.balance);
        }
    }

    fclose(report);

    printf("Report Generated Successfully\n");
    printf("File Name: BankReport.txt\n");
}