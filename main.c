#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main()
{
    FILE *fptr;
start:
    fptr = fopen("highscore.txt", "r");
    if (fptr == NULL) {
        fptr = fopen("highscore.txt", "w");
        fclose(fptr);
    }
    char bestPlayer[50];
    int highscore = 0;
    fgets(bestPlayer, 49, fptr);
    fscanf(fptr,"%d", &highscore);
    fclose(fptr);
    if (highscore <= 0) {
        printf("TAU Says\t\tHighscore: None\n1: Start Game\n2: Highscore\nAny Other Key: Quit\n");
    }
    else {
        printf("TAU Says\t\tHighscore:%d, by %s1: Start Game\n2: Highscore\nAny Other Key: Quit\n", highscore, bestPlayer);
    }
    char choice;
    scanf(" %c", &choice);
    if(choice == '1') {
        //game start
        int runde = 1;
        int score = 0;
        int zahlListe[50];
        int inputs[50];
        while (1)
        {
            printf("Current Level: #%d\n\n", runde);
            srand(time(NULL));
            zahlListe[runde-1] = ((rand()%4)+1);
            printf("Numbers: ");
            for (int i=0; i<runde; i++) {
                printf("%d ", zahlListe[i]);
            }
            int sleepMilisec;
            if (runde == 1 || runde == 2) {
                sleepMilisec = 3000;
            }
            else {
                sleepMilisec = runde*1000;
            }
            Sleep(sleepMilisec);
            //clear the line of numbers
            printf("\33[2K\r");
            printf("\n");

            for (int i=0; i<runde; i++) {
                int currentInput;
                scanf("%d", &currentInput);
                inputs[i] = currentInput;
            }

            for (int i=0; i<runde; i++) {
                if (inputs[i] != zahlListe[i]) {
                    printf("False :(\n");
                    printf("\nYour Score: %d\n", score);
                    if (score > highscore) {
                        char name[50];
                        printf("New highscore! What is your name?:");
                        scanf(" %s", name);
                        fptr = fopen("highscore.txt", "w");
                        fputs(name, fptr);
                        fprintf(fptr, "\n%d", score);
                        fclose(fptr);
                    }
                    runde = 1;
                    score = 0;
                    goto start;
                }
            }
            runde++;
            score++;
            printf("Right!");
            Sleep(2000);
            //clear terminal
            printf("\e[1;1H\e[2J");
        }
    }
    else if (choice == '2'){
        printf("--Highscore--\nName: %sScore: %d\n\n", bestPlayer, highscore);
        goto start;
    }
    else {
      exit(0);
    }
}
