#include "ErrorHandlers.h"


void handleFinErrors(int error)
{
   switch(error)
   {
      case OPEN_FILE_ERROR:
	 printf("Файла с данным именем не существует\n Данные не были считаны\n");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 break;
      case RWFILE_ERROR:
	 printf("Ошибка чтения символа\n Часть данных была считана");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 break;
      case ALLOC_ERROR:
	 perror("Не хватает ОЗУ");
	 exit(1);
   }
}

void handleFoutErrors(int error)
{
   switch(error)
   {
      case OPEN_FILE_ERROR:
	 printf("Не удалось открыть или создать файл\n");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 break;
      case RWFILE_ERROR:
	 printf("Ошибка записи в файл\n Часть данных была записана");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 break;
   }
}

int handleInputKeyErrors(int error)
{
   switch(error)
   { case WORD_OVERFLOW:
	 printf("Размер ключевого слова превышает 128 символов\n");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 return FAIL;
      case BAD_STRING:
	 printf("Не корректный ввод слова\n");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 return FAIL;
      case ALLOC_ERROR:
	 perror("Не хватает ОЗУ");
	 exit(1);
   }
   return SUCCESS;
}

int handleInputValueErrors(int error)
{
   switch(error)
   {
      case BAD_STRING:
	 printf("Не корректный ввод толкования\n");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 return FAIL;
      case ALLOC_ERROR:
	 perror("Не хватает ОЗУ");
	 exit(1);
   }
}

void handleAddErrors(int error)
{
   switch(error)
   {
      case KEY_EXIST:
	 printf("Толкование для данного слова уже существует\n");
	 printf("Для продолжения нажмите Enter\n");
	 getchar();
	 break;
      case ALLOC_ERROR:
	 perror("Не хватает ОЗУ");
	 exit(1);
   }
}
