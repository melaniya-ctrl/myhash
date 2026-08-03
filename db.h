#ifndef DB_H
#define DB_H

#include "sqlite3.h"

// Инициализация базы данных (открытие/создание таблицы)
// Возвращает 0 при успехе, -1 при ошибке
int init_database(const char *db_filename);

// Закрытие базы данных (вызывать при завершении программы)
void close_database(void);

// Вставка логина, хеша пароля и соли в таблицу
// Возвращает 0 при успехе, -1 при ошибке
int insert_hash_to_db(const char *login, const char *password_hash, const char *salt_value);

#endif
