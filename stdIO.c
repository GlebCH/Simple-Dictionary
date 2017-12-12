#include "stdIO.h"

int stdInputKey(char** key)
{
   size_t i = 0, size = 129;
   (*key) = (char*)malloc(size * sizeof(char));
   if((*key) == NULL) return ALLOC_ERROR;// malloc не смог выделить память

   char c;
   while((c = getchar()) == ' ' || c == '\t');// считываем начальные пробельные символы
   while(c != '\n' && c != ' ' && c != '\t')
   {
      (*key)[i++] = tolower(c);
      if(i == 128) 
      {
	 free(*key);
	 return WORD_OVERFLOW;// переполнение слова
      }
      c = getchar();
   }
   
   if(i == 0)// нет непробельных символов в строке
   {
      free(*key);
      return BAD_STRING;
   }
   while(c != '\n') c = getchar();//убираем лишние из потока

   (*key)[i] = '\0';
   
   return SUCCESS;
}

int stdInputValue(char** value)
{
   size_t i = 0, size = 140;// twitter
   (*value) = (char*)malloc(size * sizeof(char));
   if((*value) == NULL) return ALLOC_ERROR;//calloc не смог выделить память

   int c;
   while((c = getchar()) == ' ' || c == '\t');// считываем начальные пробельные символы
   while(c != '\n')
   {
      (*value)[i++] = c;
      if(i == size-1)
      {
	 size += 140;
	 (*value) = (char*)realloc((*value), size * sizeof(char));
	 if((*value) == NULL) return ALLOC_ERROR;//calloc не смог выделить память
      }
      c = getchar();
   }
   if(i == 0)
   {
      free(*value);
      return BAD_STRING;
   }
   (*value)[i] = '\0';

   return SUCCESS;
}


