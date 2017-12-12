#ifndef __MY_ERROR_HANDLERS__
#define __MY_ERROR_HANDLERS__

#include "stdafx.h"


void handleFinErrors(int); // обработчик ошибок считывания словаря с диска

void handleFoutErrors(int); // обработчик ошибок сохранения словаря на диск

int handleInputKeyErrors(int); // обработчик ошибок ввода слова в терминале

int handleInputValueErrors(int); // обработчик ошибок ввода толкования в терминале

void handleAddErrors(int); // обработчик ошибок добавления в хеш-таблицу


#endif
