#include "stdafx.h"
#include "Hashtable.h"
#include "stdIO.h"
#include "fileIO.h"
#include "ErrorHandlers.h"

void printMenu()
{
	system("clear");
	printf("1. Add\n");
	printf("2. Get\n");
	printf("3. Remove\n");
	printf("q Exit\n");
}


int main(int argc, char** argv)
{
   Hashtable* htable = getNewHashtb(1000, 0);
   if(htable == NULL)
   {
      perror("Не хватает ОЗУ\n");
      return FAIL;
   }


   char* key = NULL;
   char* value = NULL;
	
   if(argc > 2)
   {
      perror("too many arguments!\n");
      return FAIL;
   }
   else if(argc == 2) handleFinErrors(finHtable(htable, argv[1]));
	
   printMenu();

   char c = getchar();
   char trash = getchar();
   while(c != 'q')
   {
      switch(c)
      {
	 case '1':
	    printf("Введите слово: ");
	    if(!handleInputKeyErrors(stdInputKey(&key)))
	    {
	       
	       printf("Введите толкование: ");
	       if(!handleInputValueErrors(stdInputValue(&value)))
	       {
		  handleAddErrors(put(&htable, key, value));
	       }
	    }
	    break;
	 case '2':
	    printf("Введите слово для поиска: ");
	    if(!handleInputKeyErrors(stdInputKey(&key)))
	    {
	       const char* tmp = get(htable, key);

	       if(tmp != NULL) printf("%s\n", tmp);
	       else printf("Толкования для данного слова нет\n");

	       printf("Для продолжения нажмите Enter\n");
	       getchar();

	       free(key);
	    }
	    break;
	 case '3':
	    printf("Введите слово для удаления: ");
	    if(!handleInputKeyErrors(stdInputKey(&key)))
	    {
	       if(delete(htable, key)) printf("В словаре нет данного слова\n");

	       printf("Для продолжения нажмите Enter\n");
	       getchar();

	       free(key);
	    }
	    break;
      }
      system("clear");
      printMenu();

      c = getchar();
      trash = getchar();
   }	

	
   handleFoutErrors(foutHtable(htable));
   //freeHashtb(htable);// по идее при завершении программа память освобождается,
   return SUCCESS;
}
