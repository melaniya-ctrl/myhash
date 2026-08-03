#include "db.h"
#include <stdio.h>
#include <glib.h>

static sqlite3 *db = NULL;

// Открывается база данных и создаётся таблица
int init_database(const char *db_filename) {
    int rc = sqlite3_open(db_filename, &db);
    if (rc != SQLITE_OK) {
        g_printerr("Не удалось открыть БД: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Создаётся таблица с полем для соли
    const char *sql_create =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "login TEXT NOT NULL, "
        "password_hash TEXT NOT NULL, "
        "salt TEXT NOT NULL, "
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    char *err_msg = NULL;
    rc = sqlite3_exec(db, sql_create, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK) {
        g_printerr("Ошибка создания таблицы: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        db = NULL;
        return -1;
    }
    return 0;
}

// Закрывается соединение с базой
void close_database(void) {
    if (db) {
        sqlite3_close(db);
        db = NULL;
    }
}

// Добавляется логин, хеш пароля и соль
int insert_hash_to_db(const char *login, const char *password_hash, const char *salt_value) {
    // Проверка на открытие базы данных
    if (!db) {
        g_printerr("База данных не открыта\n");
        return -1;
    }

    // Готовится запрос для вставки новой записи
    const char *sql_insert = "INSERT INTO users (login, password_hash, salt) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        g_printerr("Ошибка подготовки запроса: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Подставляются данные вместо знаков ?
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password_hash, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, salt_value, -1, SQLITE_TRANSIENT);

    // Выполняется запрос
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        g_printerr("Ошибка вставки: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}
