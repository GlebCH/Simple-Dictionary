#include "Hashtable.h"

size_t getHash(const char* const str, const size_t htableSize)
{
   size_t hash = 0, p_pt = 1;
   const unsigned short p = 43;
   for(const char* it = str;*it != '\0';it++)
   {
      hash += (unsigned short)(*str) * p_pt; 
      p_pt *= p;
   }

   return hash % htableSize;
}


void freeHashtb(Hashtable* htable)
{
   for(size_t i = 0;i < htable->size;++i)
   {
      if(htable->table[i].key != NULL)
      {
	 free(htable->table[i].key);
	 free(htable->table[i].value);
			
	 Bucket* it = htable->table[i].nextBucket;
	 while(it != NULL)
	 {
	    Bucket* trash = it;
	    it = it->nextBucket;
	    free(trash->key);
	    free(trash->value);
	    free(trash);
	 }
      }		
   }
   free(htable->table);
   free(htable);
}

Hashtable* getNewHashtb(size_t size, size_t completed)
{
   Hashtable* nHtable = (Hashtable*)malloc(sizeof(Hashtable));
   if(nHtable == NULL) return NULL;

   nHtable->size = size;
   nHtable->completed = completed;

   nHtable->table = (Bucket*)calloc(nHtable->size, sizeof(Bucket));
   if(nHtable->table == NULL) return NULL;

   return nHtable;
}

Hashtable* reHashtb(Hashtable* htable)
{
   Hashtable* nHtable = getNewHashtb(htable->size * 2, htable->completed);
   if(nHtable == NULL) return NULL;

   for(size_t i = 0;i < htable->size; ++i)
   {
      if(htable->table[i].key != NULL)
      {
	 put(&nHtable, htable->table[i].key, htable->table[i].value);
      }

      Bucket* it = htable->table[i].nextBucket;
      while(it != NULL)
      {
	 Bucket* tmp = it;
	 put(&nHtable, it->key, it->value);
	 it = it->nextBucket;
	 free(tmp);
      }
   }
   free(htable->table);
   free(htable);

   return nHtable;
}

int put(Hashtable** htable, char* const key, char* const value)
{
   size_t i = getHash(key, (*htable)->size);	
   if((*htable)->table[i].key == NULL) 
   {
      (*htable)->table[i].key = key;
      (*htable)->table[i].value = value;
   }	
   else
   {
      if(!strcmp((*htable)->table[i].key, key)) return KEY_EXIST; // слово уже существует в словаре
      Bucket* it = (*htable)->table[i].nextBucket;

      while(it != NULL)
      {
	 if(!strcmp(it->key, key)) return KEY_EXIST;
	 it = it->nextBucket;
      }
      it = (Bucket*)calloc(1, sizeof(Bucket));
      if(it == NULL) return ALLOC_ERROR;
      it->key = key;
      it->value = value;
   }

   (*htable)->completed++;
   if(((float)(*htable)->completed / (*htable)->size) > 0.75)
   {
      (*htable) = reHashtb(*htable);
      if((*htable) == NULL) return ALLOC_ERROR; // не хватило оперативной памяти для увеличения таблицы
   }
   return SUCCESS;
}


const char* const get(const Hashtable* const htable, const char* const key)
{
   size_t i = getHash(key, htable->size);
   if(htable->table[i].key == NULL) return NULL; // данного слова нет в таблице
   if(!strcmp(htable->table[i].key, key)) return htable->table[i].value;
   else
   {
      Bucket* it = htable->table[i].nextBucket;
      while(it != NULL)
      {
	 if(!strcmp(it->key, key)) return it->value;
	 it = it->nextBucket;
      }
      

   }
   return NULL; // данного слова нет в таблице
}

int delete(Hashtable* htable, const char* const key)
{
   size_t i = getHash(key, htable->size);
   if(htable->table[i].key == NULL) return FAIL;
   Bucket* it = htable->table[i].nextBucket;
   if(!strcmp(htable->table[i].key, key)) 
   {
      free(htable->table[i].key);
      free(htable->table[i].value);

      if(it == NULL)
      {
	 htable->table[i].key = NULL;
	 htable->table[i].value = NULL;

	 return SUCCESS; // удачное завершение удаления
      }
      else
      {
	 htable->table[i].key = it->key;
	 htable->table[i].value = it->value;
	 htable->table[i].nextBucket = it->nextBucket;	
	 free(it);
	 return SUCCESS; // удачное завершение удаления
      }	
   }
   else
   {
      Bucket* prev = &htable->table[i];
      while(it != NULL)
      {
	 if(!strcmp(it->key, key))
	 {
	    free(it->key);
	    free(it->value);
	    prev->nextBucket = it->nextBucket;
	    free(it);
	    return SUCCESS; // удачное завершение удаления
	 }	
	 it = it->nextBucket;
	 prev = prev->nextBucket;
      }

   }
   return FAIL; // Слова нет в таблице
}
