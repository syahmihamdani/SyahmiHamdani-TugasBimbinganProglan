//Nama: Syahmi Hamdani
//NPM: 2306220532

//Program: Casino Roulette
//Modul: File Handling dan Queue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>   

typedef struct queue{
    char *color;
    struct queue *next;
}Queue;

typedef Queue *QueuePtr;

void red();
void reset();
void black();
void welcomeMenu(void);
void signupMenu(void);
int loginMenu(void);
void mainMenu(void);
void profile(int b, float w, int l, int bw, int rw, int bl, int rl, float p, int cw, int cl);
void printHelp(void);
void printHistory(QueuePtr currentPtr);
void enqueue(QueuePtr *headPtr, QueuePtr *tailPtr, char color[5]);
void dequeue(QueuePtr *headPtr, QueuePtr *tailPtr);
int queueSize(QueuePtr head);


int main(void){

    QueuePtr headPtr = NULL;
    QueuePtr tailPtr = NULL;

    int choice = 0, back = 0, loginSuccess, 
    bet, color, userSize = 0, colorChoice = 0, 
    bal = 0, chips = 0, loss = 0,
    blackWin = 0, redWin = 0, redLoss = 0,
    blackLoss = 0, chipsWon = 0, 
    chipsLost = 0;
    float wins = 0.0, played = 0.0;

    do{
        back = 0;
        do{
            welcomeMenu();
            scanf("%d", &choice);
            system("cls");
            while(getchar() != '\n');        
        }while(choice != 1 && choice != 2);

        switch(choice){
            case 1:
                signupMenu();
                userSize++;
                printf("Sign up success. Going back to menu!\n\n");
                system("pause");
                system("cls");
                back = 1;
                break;
            case 2:
                loginSuccess = loginMenu();
                system("pause");
                system("cls");
                back = !loginSuccess;
                break;
            default:
                break;
        }
    }while(back == 1);

    do{
        back =0;
        do{
            system("cls");
            mainMenu();
            scanf("%d", &choice);
            system("cls");
            while(getchar() != '\n');
        }while(choice < 1 || choice > 7);

        switch(choice){
            case 1:
                if (bal == 0){
                    printf("You've 0 chips in your balance!. Please aqcuire some.\n\n");
                    system("pause");
                    back = 1;
                    break;
                }
                else{
                    printf("Place your bet: $");
                    scanf("%d", &bet);
                    while(bet > bal){
                        system("cls");
                        printf("\nNot enough chips. Current balance: $%d\n", bal);
                        printf("Place your bet: $");
                        scanf("%d", &bet);
                    }
                    system("cls");
                    red();
                    printf("1. Red\n");
                    black();
                    printf("2. Black\n");
                    reset();
                    printf("-----------------------\n");
                    do{
                        printf("-> ");
                        scanf("%d", &colorChoice);
                    }while(colorChoice < 1 || colorChoice > 2);
                    printf("-----------------------\n");

                    color = rand() % 2 + 1;

                    switch(color){
                        case 1: //red
                        red();
                            if(color == colorChoice){
                                bal += bet * 2;
                                wins++;
                                redWin++;
                                chipsWon += bet * 2;
                                printf("The ball lands on RED. You've won $%d!\n\n", bet * 2);
                            }else{
                                printf("The ball lands on RED. You've lost $%d!\n\n", bet);
                                bal -= bet;
                                loss++;
                                redLoss++;
                                chipsLost += bet;
                                }
                            reset();
                            system("pause");
                            enqueue(&headPtr, &tailPtr, "RED");
                            break;
                        case 2: //black
                            black();
                            if(color == colorChoice){
                                bal += bet * 2;
                                wins++;
                                blackWin++;
                                chipsWon += bet * 2;
                                printf("The ball lands on BLACK. You've won $%d!\n\n", bet * 2);
                            }else{
                                bal -= bet;
                                loss++;
                                redLoss++;
                                chipsLost += bet;
                                printf("The ball lands on BLACK. You've lost $%d!\n\n", bet);
                            }
                            reset();
                            system("pause");
                            enqueue(&headPtr, &tailPtr, "BLACK");
                            break;
                        default:
                            break;
                    }
                    printf("Current Balance: $%d", bal);
                    played += 1.0;
                    back = 1;
                    
                }
                //scanf("%d", &color);
                //roulette(bet, color);
                break;
            case 2:
                printf("=== Aqcuiring Chips ===\n");
                printf("How many chips: \n-> $");
                scanf("%d", &chips);
                printf("$%d Aqcuired!\n\n", chips);
                system("pause");
                bal += chips;
                back = 1;
                break;
            case 3:
                printf("-------------------------------------\n");
                printHistory(headPtr);
                printf("-------------------------------------\n");
                system("pause");
                back = 1;
                break;
            case 4:
                system("cls");
                profile(bal, wins, loss, blackWin, redWin, blackLoss, redLoss, played, chipsWon, chipsLost);
                system("pause");
                back = 1;
                break;
            case 5:
                system("cls");
                printHelp();
                system("pause");
                back = 1;
                break;
            case 6:
                system("cls");
                printf("Exiting casino. Thank you for playing!");
                back = 0;
                break;
            default:
                break;
        }
    }while(back == 1);
    return 0;

}

void welcomeMenu(void){
    printf("===== WELCOME =====\n"
            "| 1. Sign Up      |\n"
            "| 2. Log in       |\n"
            "===================\n"
    );
    printf("-> ");
}

void signupMenu(){
    FILE *file, *file2;
    file = fopen("users.txt", "r");
    char buffer[2048];
    char bufferCheck[2048];
    int taken = 0;

    do{
        printf("Enter username [max 10 characters]: ");
        scanf("%s", buffer);
        while(fscanf(file, "%s", bufferCheck) != EOF){
            if(strcmp(buffer, bufferCheck) == 0){
                printf("Username taken! Please enter a different username\n");
                system("pause");
                system("cls");
                taken = 1;
                break;
            }
            else{
                taken = 0;
            }
            
        }
        fseek(file, 0, SEEK_SET);
    }while(taken == 1);
    fclose(file);

    file = fopen("users.txt", "a");
    file2 = fopen("pass.txt ", "a");
    fprintf(file, "%s\n", buffer);
    printf("Enter password: ");
    scanf("%s", buffer);
    fprintf(file2, "%s\n", buffer);
    printf("\n");

    fclose(file);
    fclose(file2);

}

int loginMenu(void){
    FILE *file, *file2;
    file = fopen("users.txt", "r");
    file2 = fopen("pass.txt", "r");

    int readLine = 0;
    int currentLine = 1;
    int reading = 1;

    char user[2048];
    char userCheck[2048];
    char pass[2048];
    char passCheck[2048];

    printf("Enter username: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", pass);

    do{
        fscanf(file, "%s", userCheck);

        if(feof(file)){
            reading = 0;
            printf("Username not registered. Please sign up!\n");
        }
        else if(strcmp(user, userCheck) == 0){
            int found = 1;
            break;
        }
        currentLine++;

    }while(reading);

    int checkLine = currentLine;
    currentLine = 1;

    while(fscanf(file2, "%s", passCheck) != EOF){
        if(currentLine == checkLine){
            if(strcmp(pass, passCheck) == 0){
                printf("Log in successful. Entering now!\n");
                return 1;
            }
            else{
                system("cls");
                printf("Wrong Password!\n");
                system("pause");
                system("cls");
                return 0;
            }
        }

        currentLine++;
        
    }

    fclose(file);
    fclose(file2);
}

void mainMenu(void){
    printf("====== $ ROULETTE $ ======\n"
            "| 1. Start Roulette      |\n" //spin: choose red or black, gets 2x
            "| 2. Acquire Chips       |\n" //buy chips: 1 dollar = 1 chip
            "| 3. Spin History        |\n" //ex: red-black-black-red-red
            "| 4. Profile             |\n" //balance, stats
            "| 5. Help                |\n"  //help
            "| 6. Exit                |\n"  //exit program
            "==========================\n"
            "-> "
    );
}

void printHelp(void){
    printf("$ Start Roulette -> Choose how much chips to bet. Pick red or black. If correct, win 2x bet amount \n"
            "$ Acquire Chips -> Add as many chips as you like. Chips added to balance\n"
            "$ Spin History -> See where the spin landed on the last 5 rounds\n"
            "$ Profile -> See balance, stats\n"
            "$ Exit -> Exit casino.\n");
}

void enqueue(QueuePtr *headPtr, QueuePtr *tailPtr, char color[5]){

    if(queueSize(*headPtr) == 5){
        dequeue(headPtr, tailPtr);
    }

    QueuePtr newNode;
    newNode = malloc(sizeof(Queue));

    if(newNode == NULL){
        printf("Failed to allocate memory");
        return;
    }
    else{
        newNode->color = malloc(sizeof(char) * 5);
        if(newNode->color == NULL){
            printf("Failed to allocate memory");
            free(newNode);
            return;
        }
        strcpy(newNode->color, color);
        newNode->next = NULL;

        if(*headPtr == NULL){
            *headPtr = newNode;
        }
        else{
            (*tailPtr)->next = newNode;
        }
        *tailPtr = newNode;
    }
}

void dequeue(QueuePtr *headPtr, QueuePtr *tailPtr){
    QueuePtr temp;
    char *color;
    if(*headPtr == NULL){
        printf("No rounds played!\n");
    }
    else{
        temp = *headPtr;
        *headPtr = (*headPtr)->next;

        free(temp->color);
        free(temp);

        if(*headPtr == NULL){
            *tailPtr = NULL;
        }
    }
}

void printHistory(QueuePtr current){
    if(current == NULL){
        printf("No rounds played\n");
    }
    else{
        while(current != NULL){
            if(strcmp(current->color, "RED") == 0){
                red();
                printf("%s -->  ", current->color);
                reset();
            }
            else{
                black();
                printf("%s -->  ", current->color);
                reset();
            }
            current = current->next;
        }
        printf("[Oldest to Newest]\n");
    }
}

int queueSize(QueuePtr head) {
    int size = 0;
    QueuePtr current = head;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}

void profile(int b, float w, int l, int bw, int rw, int bl, int rl, float p, int cw, int cl){
    printf("============ BALANCE ==========\n");
    printf(" $ Balance: $%d            \n", b);
    printf(" $ Chips Won: +$%d          \n", cw);
    printf(" $ Chips Lost: -$%d         \n", cl);
    printf("============  STATS  ==========\n");
    printf(" $ Roulette Spins: %.2g        \n", p);
    printf(" $ Wins: %.2g               \n", w);
    printf(" $ Win Percentage: %.2f%%    \n", (w/p) * 100);    
    printf(" $ Red Wins: %d              \n", rw);
    printf(" $ Black Wins: %d            \n", bw);
    printf(" $ Losses: %d                \n", l);
    printf(" $ Red Losses: %d            \n", rl);
    printf(" $ Black Losses:%d           \n", bl);
    printf("===============================\n");
}

void red(){
    printf("\033[1;31m");
}

void reset(){
    printf("\033[0m");
}

void black(){
    printf("\033[0;30m");
}