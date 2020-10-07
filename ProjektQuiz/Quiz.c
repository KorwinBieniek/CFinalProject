#include "Quiz.h"
#include "switches.h"
#include "structures.h"

int OpenQuestions(int nrOfQ, char* filename)
{
    FILE* fp = fopen(filename, "r"); //otworzenie pliku z pytaniami podanego jako parametr
    checkIfOpen(fp);
    int i = 0, x = 0, z = 0, points = 0; //liczniki oraz liczba punktów
    QUESTIONS *questions = (QUESTIONS*) malloc(100 * sizeof(QUESTIONS)); //Tablica dla pytań, które zostaną wczytane z pliku
    srand(time(NULL)); //generowanie losowych liczb
    int base[nrOfQ]; //generowanie bazy pytań dla ilości pytań z pliku podanej przez użytkownika
    while (!feof(fp))
    {
        fRead(questions, i, fp);
        i++;
    }
    int flag[i];
    nrOfQ = tooManyQuestions(nrOfQ, i);
    while(z < nrOfQ) //generacja pseudolosowych liczb, warunek sprawdza czy sie nie powtarzaja
    {
        int num = (rand() % (i)); //pseudolosowa liczba
        if(num != flag[num])
        {
            base[z] = num;
            flag[num] = num;
            z++;
        }
    }
    while(x < nrOfQ) //dopoki nie osiagnie liczby pytan wybranej przez uzytkownika
    {
        system("cls");
        printf("\n\nPytanie %d/%d\n\n%s\nA) %s\nB) %s\nC) %s\nD) %s\n\n\n", x+1, nrOfQ, questions[base[x]].code, //wysiwetl pytanie
               questions[base[x]].a, questions[base[x]].b, questions[base[x]].c, questions[base[x]].d);
                       char answer = toupper(getch());
               if(answer != 'A' && answer != 'B' && answer != 'C' && answer != 'D') printf("Nie ma odpowiedzi %c, nie zdobywasz punktu\n\n", answer);
        if(checkAnswer(answer, questions, x, base) == 1) //jezeli poprawna odpowiedz to dodaj punkt
            points++;
        printf("Press any key to continue to the next question"); //ekran pauzy
        getch();
        x++;
    }
    free(questions);
    fclose(fp);
    return points; //zwraca liczbe punktow
}
//////////////////////////////////////////////////////////////////////////////
int checkIfOpen(FILE* fp)
{
    if (fp == NULL)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\nNo such file");
        printf("\033[0m");
        exit(0);
    }
    return 0;
}

int tooManyQuestions(int nrOfQ, int i)
{
    if(nrOfQ > i) //zabezpieczenie na wypadek, gdyby uzytkownik chcial odpowiedziec na wiecej pytan niz jest w pliku
    {
        system("cls");
        printf("\t\t\t\tThe file has only %d questions.\n\t   Changing the number of questions to answer to max questions in the file.", i);
        printf("\n\n\n\t\t\t\tPress any key to continue");
        nrOfQ = i;
        getch();

        return nrOfQ;
    }
    else
        return nrOfQ;
}

void fRead(QUESTIONS questions[], int i, FILE* fp) //wczytaj pytana z pliku do tablicy
{
    fgets(questions[i].code,sizeof(questions[i].code), fp);
    fgets(questions[i].correct,sizeof(questions[i].correct), fp);
    fgets(questions[i].a,sizeof(questions[i].a), fp);
    fgets(questions[i].b,sizeof(questions[i].b), fp);
    fgets(questions[i].c,sizeof(questions[i].c), fp);
    fgets(questions[i].d,sizeof(questions[i].d), fp);
}

int checkAnswer(char answer, QUESTIONS questions[], int x, int base[])
{
    int correct = atoi(questions[base[x]].correct); //wczytaj poprawna odpowiedz z plku i przeksztalc na cyfre
    if((answer == 'A' && correct == 1) || (answer == 'B' && correct == 2) || (answer == 'C' && correct == 3) || (answer == 'D' && correct == 4))
    {
        printf("\033[0;32m"); //zmiana koloru w przypadku dobrej odpowiedzi
        printf("Correct answer!\n\n");
        printf("\033[0m"); //reset koloru
        return 1;
    }

    else
    {
        printf("\033[1;31m"); //zmiana koloru w przypadku zlej odpowiedzi
        printf("Incorrect answer!\n\n");
        printf("\033[0m"); //reset koloru

        return 0;
    }
}

char* getTime() //funkcja pobierajaca date podczas procesu kompilacji, aby moc zapisac date do pliku
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    //printf ( "Current local time and date: %s", asctime (timeinfo) );

    return asctime(timeinfo);
}

void mainMenu(char* user)
{
    printf("\n\t\t\tWelcome %s", user);
    printf("\n\t\t\t      to ");
    printf("\n\t\t       the Quiz Program ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t - Press N to start a new game");
    printf("\n\t\t - Press any other key to quit the program             ");
    printf("\n\t\t________________________________________\n\n");
}

void startGame(int nrOfQ, char* filename)
{
    system("cls"); //czyszczenie ekranu
    printf("\n\t\t   You've chosen to answer %i questions from the question base %s", nrOfQ, filename);
    printf("\n\t\t\t   You can answer all the questions");
    printf("\n\t\t   Your score will be the amount of correctly answered questions");
    printf("\n\n\n\t\t\t\t   Press any key to continue");
    getch(); //ekran pauzy
}

char* TxtDel(char* name) //przy pobraniu nazwy pliku np test.txt, usuwana jest koncowka .txt
{
    int i = 0;
    while(name[i] != '\0')
    {
        i++;

    }
    name[i-4] = '\0';
    return name;
}

void saveToFile(char* filename, int nrOfQ, char* user)
{
    FILE *f;
    int score = OpenQuestions(nrOfQ, filename); //funkcja OpenQuestions zwraca liczbe punktow

    const char* name = filename;
    TxtDel(name); //usun koncowke pliku
    const char* extension = "_score.txt"; //dodaj czlon i koncowke

    char* name_with_extension;
    name_with_extension = malloc(strlen(name)+10);
    strcpy(name_with_extension, name);
    strcat(name_with_extension, extension); // polacz czlon i nazwe pliku

    system("cls");
    // czyszczenie ekranu
    printf("\n\n\t\t\tCongratulations! You have finished the quiz with the score: %d\n\t\t\t     Now your score will be saved in %s\n\n\n\n", score, name_with_extension); //informacja dla uzytkownika o punktach

    f = fopen(name_with_extension,"r");

    if (f == NULL)
    {
        printf("\033[1;31m"); //jezeli plik z punktacja nie istnieje, to jest utworzony nowy
        printf("\nCannot find a file %s - creating a new one", name_with_extension);
        printf("\033[0m");
        f = fopen(name_with_extension,"w");
        fclose(f);
    }
    f=fopen(name_with_extension,"a");
    free(name_with_extension);
    fprintf(f,"\nDate: %sPlayer: %s\nCorrect answers: %d\n________________________________________________",getTime(),user,score); //zapis danych do pliku
    fclose(f);
}
