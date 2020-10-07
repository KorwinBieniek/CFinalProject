#include "Quiz.h"
#include "switches.h"
#include "structures.h"

int main(int argc, char *argv[] )
{
    if(argc < 7 || argc >= 8) printf("Podaj poprawne argumenty:\n-o dla pliku wejsciowego\n-n dla nazwy uzytkownika\n-q dla liczby pytan"); //Wymagane podanie dokładnej liczby argumentów, inaczej program zakończy działanie przedwcześnie
    else
    {
        int nrOfQ = 1; //ilosc pytań
        char* filename; //nazwa pliku
        char* user = "user"; //nazwa użytkownika
        int opt; //zmienna odpowiadająca za prawidłowe działanie przełączników
        do
        {
            if(inputHandling(opt, &nrOfQ, argc, argv, &filename, &user) == 0) //Funkcja obsługująca przełączniki
                return 0;
        }while((opt = getopt(argc, argv, "onq")) != -1); //Możliwe przełączniki, getopt parsuje argumenty linii poleceń
        if(nrOfQ <= 0)
        {
            printf("Blad: Wybrano zla liczbe pytan pytan\n\n");
            exit(0);
        }

        char choice; //wybór opcji z menu głównego
        mainMenu(user); //Menu główne
        choice=toupper(getch());
        if (choice=='N') //Rozpoczęcie nowej gry po wpisaniu 'n' lub 'N', jezeli inny znak to zakończenie działania programu
        {
            startGame(nrOfQ, filename); //funkcja odpowiadająca za rozpoczęcie rozgrywki
            saveToFile(filename, nrOfQ, user); //funkcja odpowiadająca za zapisanie wyniku do pliku tekstowego
        }
        else exit(0);
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////

