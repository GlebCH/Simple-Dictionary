#ifndef _FILE_IO_
#define _FILE_IO_

#include "stdafx.h"
#include "Hashtable.h"


int fileInputKey(char**, FILE*); // считывает слово с файла

int fileInputValue(char**, FILE*); // считывание толкования с файла

int finHtable(Hashtable*, char* fileName); // считывает хэш-таблицу с диска

int foutBucket(const char*, const char*, FILE*); // записывает ячейку хэш-таблицы на диск
						 // используется в foutHtbale

int foutHtable(const Hashtable* const); // записывает хэш-таблицу на диск



#endif
