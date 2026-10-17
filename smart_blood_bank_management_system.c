#include <stdio.h>

#define MAX_DONORS 100
#define MAX_REQUESTS 100
#define QUEUE_SIZE 20
#define BLOOD_GROUPS 8

struct Donor {
    int id;
    char name[50];
    int age;
    char phone[20];
    int bloodGroup;
    int totalDonations;
    int lastDay, lastMonth, lastYear;
    int hasDonated;
};

struct Request {
    int id;
    char hospital[60];
    int bloodGroup;
    int units;
    int status; /* 0 = pending, 1 = fulfilled */
};

struct Transaction {
    int id;
    int bloodGroup;
    int units;
    int type; /* 1 = ADD, 2 = ISSUE */
};

int main(void) {
    const char bloodNames[BLOOD_GROUPS][4] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    struct Donor donors[MAX_DONORS];
    struct Request requests[MAX_REQUESTS];
    struct Transaction queue[QUEUE_SIZE];
    int stock[BLOOD_GROUPS] = {10, 5, 8, 4, 6, 3, 12, 5}; /* fictional demo stock */
    int donorCount = 0, requestCount = 0;
    int front = 0, rear = -1, queueCount = 0;
    int nextDonorId = 1001, nextRequestId = 5001, nextTransactionId = 1;
    int choice = 0;

    while (choice != 12) {
        int i, j;
        printf("\n========== SMART BLOOD BANK MANAGEMENT SYSTEM ==========\n");
        printf("1. Register donor\n");
        printf("2. Display donors and donation history\n");
        printf("3. Record donor donation and check interval\n");
        printf("4. Display blood stock\n");
        printf("5. Add stock using enqueue\n");
        printf("6. Issue stock using enqueue\n");
        printf("7. Process next transaction using dequeue\n");
        printf("8. Display pending transactions\n");
        printf("9. Add hospital blood request\n");
        printf("10. Display hospital requests\n");
        printf("11. Fulfil a hospital blood request\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please restart and enter menu numbers only.\n");
            return 1;
        }

        switch (choice) {
            case 1: {
                int group;
                if (donorCount >= MAX_DONORS) {
                    printf("Donor storage is full.\n");
                    break;
                }
                donors[donorCount].id = nextDonorId++;
                printf("Enter donor name: ");
                scanf(" %49[^\n]", donors[donorCount].name);
                printf("Enter age: ");
                if (scanf("%d", &donors[donorCount].age) != 1 || donors[donorCount].age < 1 || donors[donorCount].age > 120) {
                    printf("Invalid age. Donor not registered.\n");
                    while (getchar() != '\n') { }
                    break;
                }
                printf("Enter phone number (digits or + allowed): ");
                scanf(" %19s", donors[donorCount].phone);
                printf("Select blood group:\n");
                for (i = 0; i < BLOOD_GROUPS; i++) printf("%d. %s\n", i + 1, bloodNames[i]);
                printf("Enter choice (1-8): ");
                if (scanf("%d", &group) != 1 || group < 1 || group > 8) {
                    printf("Invalid blood group. Donor not registered.\n");
                    while (getchar() != '\n') { }
                    break;
                }
                donors[donorCount].bloodGroup = group - 1;
                donors[donorCount].totalDonations = 0;
                donors[donorCount].lastDay = 0;
                donors[donorCount].lastMonth = 0;
                donors[donorCount].lastYear = 0;
                donors[donorCount].hasDonated = 0;
                printf("Donor registered successfully. Donor ID: %d\n", donors[donorCount].id);
                donorCount++;
                break;
            }

            case 2:
                if (donorCount == 0) {
                    printf("No donor records available.\n");
                } else {
                    printf("\n--- DONOR RECORDS ---\n");
                    for (i = 0; i < donorCount; i++) {
                        printf("ID: %d | Name: %s | Age: %d | Phone: %s | Blood: %s | Donations: %d",
                               donors[i].id, donors[i].name, donors[i].age, donors[i].phone,
                               bloodNames[donors[i].bloodGroup], donors[i].totalDonations);
                        if (donors[i].hasDonated)
                            printf(" | Last donation: %02d-%02d-%04d\n", donors[i].lastDay, donors[i].lastMonth, donors[i].lastYear);
                        else
                            printf(" | Last donation: Not recorded\n");
                    }
                }
                break;

            case 3: {
                int id, index = -1, day, month, year, valid = 1;
                int totalDays = 0, previousDays = 0, daysInMonth;
                printf("Enter donor ID: ");
                if (scanf("%d", &id) != 1) { printf("Invalid ID.\n"); while (getchar() != '\n') { } break; }
                for (i = 0; i < donorCount; i++) if (donors[i].id == id) index = i;
                if (index == -1) { printf("Donor ID not found.\n"); break; }
                printf("Enter donation date (DD MM YYYY): ");
                if (scanf("%d %d %d", &day, &month, &year) != 3) { printf("Invalid date input.\n"); while (getchar() != '\n') { } break; }
                if (year < 1900 || year > 2200 || month < 1 || month > 12 || day < 1) valid = 0;
                if (valid) {
                    daysInMonth = 31;
                    if (month == 4 || month == 6 || month == 9 || month == 11) daysInMonth = 30;
                    if (month == 2) {
                        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) daysInMonth = 29;
                        else daysInMonth = 28;
                    }
                    if (day > daysInMonth) valid = 0;
                }
                if (!valid) { printf("Invalid calendar date. Donation not recorded.\n"); break; }
                /* Convert the entered date to a day number, without time.h. */
                for (j = 1; j < year; j++) {
                    totalDays += 365;
                    if (j % 400 == 0 || (j % 4 == 0 && j % 100 != 0)) totalDays++;
                }
                for (j = 1; j < month; j++) {
                    int md = 31;
                    if (j == 4 || j == 6 || j == 9 || j == 11) md = 30;
                    if (j == 2) {
                        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) md = 29;
                        else md = 28;
                    }
                    totalDays += md;
                }
                totalDays += day;
                if (donors[index].hasDonated) {
                    int py = donors[index].lastYear;
                    for (j = 1; j < py; j++) {
                        previousDays += 365;
                        if (j % 400 == 0 || (j % 4 == 0 && j % 100 != 0)) previousDays++;
                    }
                    for (j = 1; j < donors[index].lastMonth; j++) {
                        int md = 31;
                        if (j == 4 || j == 6 || j == 9 || j == 11) md = 30;
                        if (j == 2) {
                            if (py % 400 == 0 || (py % 4 == 0 && py % 100 != 0)) md = 29;
                            else md = 28;
                        }
                        previousDays += md;
                    }
                    previousDays += donors[index].lastDay;
                    if (totalDays <= previousDays) {
                        printf("Donation date must be later than the previous donation date.\n");
                        break;
                    }
                    if (totalDays - previousDays < 90) {
                        printf("Donation not recorded: fewer than 90 days since the last recorded donation.\n");
                        printf("This is a classroom demo rule only; actual eligibility must be checked by qualified blood-bank staff.\n");
                        break;
                    }
                }
                donors[index].totalDonations++;
                donors[index].lastDay = day;
                donors[index].lastMonth = month;
                donors[index].lastYear = year;
                donors[index].hasDonated = 1;
                printf("Donation history updated. Total recorded donations: %d\n", donors[index].totalDonations);
                printf("Reminder: this program records history only; it does not medically determine donor eligibility.\n");
                break;
            }

            case 4:
                printf("\n--- CURRENT BLOOD STOCK (DEMO UNITS) ---\n");
                for (i = 0; i < BLOOD_GROUPS; i++) printf("%s: %d units\n", bloodNames[i], stock[i]);
                break;

            case 5:
            case 6: {
                int group, units, type = (choice == 5) ? 1 : 2;
                if (queueCount == QUEUE_SIZE) { printf("Transaction queue is full. Process a transaction before adding another.\n"); break; }
                printf("Select blood group:\n");
                for (i = 0; i < BLOOD_GROUPS; i++) printf("%d. %s\n", i + 1, bloodNames[i]);
                printf("Enter choice (1-8): ");
                if (scanf("%d", &group) != 1 || group < 1 || group > 8) { printf("Invalid blood group.\n"); while (getchar() != '\n') { } break; }
                printf("Enter number of units: ");
                if (scanf("%d", &units) != 1 || units <= 0) { printf("Units must be a positive integer.\n"); while (getchar() != '\n') { } break; }
                group--;
                if (type == 2 && stock[group] < units) { printf("Insufficient stock. Available %s stock: %d units.\n", bloodNames[group], stock[group]); break; }
                rear = (rear + 1) % QUEUE_SIZE;
                queue[rear].id = nextTransactionId++;
                queue[rear].bloodGroup = group;
                queue[rear].units = units;
                queue[rear].type = type;
                queueCount++;
                if (type == 1) stock[group] += units;
                else stock[group] -= units;
                printf("Transaction #%d added to circular queue. Type: %s.\n", queue[rear].id, type == 1 ? "ADD" : "ISSUE");
                printf("Updated %s stock: %d units.\n", bloodNames[group], stock[group]);
                break;
            }

            case 7:
                if (queueCount == 0) {
                    printf("No pending transactions in the queue.\n");
                } else {
                    printf("Processed transaction #%d: %s %d unit(s) of %s.\n",
                           queue[front].id, queue[front].type == 1 ? "ADD" : "ISSUE",
                           queue[front].units, bloodNames[queue[front].bloodGroup]);
                    printf("Stock is not changed again because it was updated when the transaction was enqueued.\n");
                    front = (front + 1) % QUEUE_SIZE;
                    queueCount--;
                    if (queueCount == 0) rear = (front + QUEUE_SIZE - 1) % QUEUE_SIZE;
                }
                break;

            case 8:
                if (queueCount == 0) {
                    printf("No pending transactions.\n");
                } else {
                    printf("\n--- PENDING TRANSACTIONS (FIFO ORDER) ---\n");
                    for (i = 0; i < queueCount; i++) {
                        int pos = (front + i) % QUEUE_SIZE;
                        printf("ID: %d | Type: %s | Blood: %s | Units: %d\n", queue[pos].id,
                               queue[pos].type == 1 ? "ADD" : "ISSUE", bloodNames[queue[pos].bloodGroup], queue[pos].units);
                    }
                }
                break;

            case 9: {
                int group, units;
                if (requestCount >= MAX_REQUESTS) { printf("Hospital request storage is full.\n"); break; }
                requests[requestCount].id = nextRequestId++;
                printf("Enter hospital name: ");
                scanf(" %59[^\n]", requests[requestCount].hospital);
                printf("Select required blood group:\n");
                for (i = 0; i < BLOOD_GROUPS; i++) printf("%d. %s\n", i + 1, bloodNames[i]);
                printf("Enter choice (1-8): ");
                if (scanf("%d", &group) != 1 || group < 1 || group > 8) { printf("Invalid blood group. Request not saved.\n"); while (getchar() != '\n') { } break; }
                printf("Enter units required: ");
                if (scanf("%d", &units) != 1 || units <= 0) { printf("Units must be a positive integer. Request not saved.\n"); while (getchar() != '\n') { } break; }
                requests[requestCount].bloodGroup = group - 1;
                requests[requestCount].units = units;
                requests[requestCount].status = 0;
                printf("Hospital request created. Request ID: %d (PENDING).\n", requests[requestCount].id);
                requestCount++;
                break;
            }

            case 10:
                if (requestCount == 0) printf("No hospital requests recorded.\n");
                else {
                    printf("\n--- HOSPITAL REQUESTS ---\n");
                    for (i = 0; i < requestCount; i++)
                        printf("ID: %d | Hospital: %s | Blood: %s | Units: %d | Status: %s\n",
                               requests[i].id, requests[i].hospital, bloodNames[requests[i].bloodGroup],
                               requests[i].units, requests[i].status ? "FULFILLED" : "PENDING");
                }
                break;

            case 11: {
                int id, index = -1, group, units;
                printf("Enter hospital request ID to fulfil: ");
                if (scanf("%d", &id) != 1) { printf("Invalid request ID.\n"); while (getchar() != '\n') { } break; }
                for (i = 0; i < requestCount; i++) if (requests[i].id == id) index = i;
                if (index == -1) { printf("Request ID not found.\n"); break; }
                if (requests[index].status == 1) { printf("This request has already been fulfilled.\n"); break; }
                group = requests[index].bloodGroup;
                units = requests[index].units;
                if (stock[group] < units) {
                    printf("Cannot fulfil request: %s has %d unit(s), but %d required. Request remains PENDING.\n", bloodNames[group], stock[group], units);
                    break;
                }
                if (queueCount == QUEUE_SIZE) { printf("Cannot fulfil request: transaction queue is full. Process pending transactions first.\n"); break; }
                rear = (rear + 1) % QUEUE_SIZE;
                queue[rear].id = nextTransactionId++;
                queue[rear].bloodGroup = group;
                queue[rear].units = units;
                queue[rear].type = 2;
                queueCount++;
                stock[group] -= units;
                requests[index].status = 1;
                printf("Request #%d for %s fulfilled. Issued %d unit(s) of %s.\n", id, requests[index].hospital, units, bloodNames[group]);
                printf("Issue transaction #%d added to queue. Remaining %s stock: %d units.\n", queue[rear].id, bloodNames[group], stock[group]);
                break;
            }

            case 12:
                printf("Exiting Smart Blood Bank Management System. Goodbye!\n");
                break;

            default:
                printf("Invalid menu choice. Please select 1-12.\n");
        }
    }
    return 0;
}
