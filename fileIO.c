#include "fileIO.h"

int fileInputKey(char** key, FILE* file)
{
   size_t i = 0, size = 129;
   (*key) = (char*)malloc(size * sizeof(char));
   if((*key) == NULL) return ALLOC_ERROR; // malloc не смог выделить память

   int c = fgetc(file);
   while(c != '\n' && c != EOF)
   {
      (*key)[i++]= c;
      c = fgetc(file);
   }
   if(c == EOF)
   {
      free(*key);
      if(feof(file) != 0) return END_OF_FILE; // файл закончился
      else return RWFILE_ERROR; // ошибка чтения символа
   }
   (*key)[i] = '\0';
   
   return SUCCESS;
}

int fileInputValue(char** value, FILE* file)
{
   size_t i = 0, size = 140;
   (*value) = (char*)malloc(size * sizeof(char));
   if((*value) == NULL) return ALLOC_ERROR; // malloc не смог выделить память

   int c = fgetc(file);
   while(c != '\n')
   {
      (*value)[i++]= c;
      if(i == size-1)
      {
	 size += 140;
	 (*value) = (char*)realloc((*value), size * sizeof(char));
	 if((*value) == NULL) return ALLOC_ERROR; // recalloc не смог выделить память
      }
      c = fgetc(file);
   }
   (*value)[i] = '\0';
// так как файл который считываем является словарем
// и мы считали успешно слово, значит толкование обязательно существует
// поэтому можем не проверять на конец строки
   return SUCCESS;
}

int finHtable(Hashtable* htable, char* name)
{
   FILE* file = fopen(name, "r");
   if(file != NULL)
   {
      int errors;
      char* key,* value;

      while(1)
      {
	 errors = fileInputKey(&key, file);
	 if(errors != SUCCESS)
	 {
	   fclose(file); 
	   return errors;
	 }

	 errors = fileInputValue(&value, file);
	 if(errors != SUCCESS)
	 {
	    fclose(file);
	    return errors;
	 }

	 put(&htable, key, value);
      }
   }
   else return OPEN_FILE_ERROR;// файла не существует с данным именем
}

int foutBucket(const char* key, const char* value, FILE* file)
{
   while(*key != '\0')
   {
      if(fputc(*key, file) == EOF)
      {
	 fclose(file);
	 return RWFILE_ERROR; // ошибка записи в файл
      }
      key++;
   }
   fputc('\n', file);

   while(*value != '\0')
   {
      if(fputc(*value, file) == EOF)
      {
	 fclose(file);
	 return RWFILE_ERROR; // ошибка записи в файл
      }
      value++;
   }
   fputc('\n', file);

   return SUCCESS;
}


int foutHtable(const Hashtable* const htable)
{
   FILE* file = fopen("user_dictionary","w");
   if(file != NULL)
   {
      int errors;
      const char* key = NULL;
      const char* value = NULL;

      for(size_t i = 0;i < htable->size;++i)
      {                                      
	 if(htable->table[i].key != NULL)
	 {
	    key = htable->table[i].key;
	    value = htable->table[i].value;

	    errors = foutBucket(key, value, file);
	    if(errors != SUCCESS) return errors;
	 }

	 Bucket* it = htable->table[i].nextBucket;
	 while(it != NULL)
	 {
	    key = it->key;
	    value = it->value;

	    errors = foutBucket(key, value, file);
	    if(errors != SUCCESS) return errors;

	    it = it->nextBucket;
	 }
      }

   }
   else return OPEN_FILE_ERROR;//проблемы с открытием/созданием файла
}
