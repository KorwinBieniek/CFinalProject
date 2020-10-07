#pragma once
#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct questions
{
    char code[200];
    char correct[3];
    char* a[50];
    char* b[50];
    char* c[50];
    char* d[50];
} QUESTIONS;

#endif // STRUCTURES_H_INCLUDED
