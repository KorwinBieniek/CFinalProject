#pragma once
#ifndef QUIZ_H_INCLUDED
#define QUIZ_H_INCLUDED

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>

char* getTime();
void mainMenu(char* user);
void startGame(int nrOfQ, char* filename);
void saveToFile(char* filename, int nrOfQ, char* user);
int checkAnswer(char answer, QUESTIONS questions[], int x, int base[]);
void fRead(QUESTIONS questions[], int i, FILE* fp);
int OpenQuestions(int nrOfQ, char* filename);
char* LastcharDel(char* name);
int tooManyQuestions(int nrOfQ, int i);
int checkIfOpen(FILE* fp);


#endif // QUIZ_H_INCLUDED
