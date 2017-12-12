#ifndef __MY_HASH_TABLE__
#define __MY_HASH_TABLE__

#include "stdafx.h"

typedef struct Hashtable Hashtable;
typedef struct Bucket Bucket;

struct Bucket			 // ячейка хеш таблицы, хранить ключ, значение
{				 // и указатель на односвязный список колизий
       	char* key;		 // колизии разрешаются методом цепочек
   	char* value;
	struct Bucket* nextBucket;
}; 

struct Hashtable		 // хэш таблица, хранит указатель на массив ячеек
{				 // размер таблицы, кол-во заполненных ячеек
	size_t completed;
	size_t size;
	struct Bucket* table;
};


size_t getHash(const char* const, const size_t); // функция хеша, по слову и размеру хэш таблицы
						 // возвращает индекс ячейки

Hashtable* getNewHashtb(size_t, size_t); // Инициализирует новую хэш таблицу
				         // принимает 2 аргумента, размер новой таблицы
					 // и кол-во заполненных ячеек

void freeHashtb(Hashtable*); // освобождает выделенную память под таблицу

Hashtable* reHashtb(Hashtable*); // обновляет хэш таблицу
				 // создает новую, увеличивая размер в 2 раза, копирует значения старой
				 // при этом индекс для каждой старой ячейки создается заново

int put(Hashtable**, char* const, char* const); // добавляет слово и толкование в таблицу
						// если заполняемость таблицы привысить 75%, обновляет


const char* const get(const Hashtable* const, const char* const); // возвращает значение по ключу

int delete(Hashtable* const, const char* const); // удаляет ячейку по ключу
#endif
