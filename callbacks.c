#include <glib.h>
#include <string.h>
#include "callbacks.h"
#include "salt.h"
#include "db.h"

// Объявляются глобальные переменные
static GtkWidget *result_parol = NULL;
static GtkWidget *result_login = NULL;
static GtkWidget *login_entry = NULL;

// Сохраняется указатель на поле ввода логина
void set_login_entry(GtkWidget *widget) {
    login_entry = widget;
}

// Сохраняются указатели на метки для вывода результатов
void set_result_widgets(GtkWidget *login_label, GtkWidget *parol_label) {
    result_login = login_label;
    result_parol = parol_label;
}

// Переключается видимость пароля (показать/скрыть)
void toggle_visibility(GtkButton *button, GtkEntry *entry) {
    gboolean visible = gtk_entry_get_visibility(entry);
    gtk_entry_set_visibility(entry, !visible);

    if (visible) {
        gtk_button_set_icon_name(button, "view-conceal-symbolic");
    } else {
        gtk_button_set_icon_name(button, "view-reveal-symbolic");
    }
}

// Обрабатывается нажатие кнопки: хеширование пароля с солью
void hash_clicked(GtkButton *button, GtkEntry *entry) {
    // Получаются данные из полей ввода
    const char *password = gtk_editable_get_text(GTK_EDITABLE(entry));
    const char *login = gtk_editable_get_text(GTK_EDITABLE(login_entry));

    // Генерируется соль
    char *salt_value = generate_salt();

    // Соединяется соль с паролем
    gchar *salted_password = g_strconcat(salt_value, password, NULL);

    // Хешируется солёный пароль
    GChecksum *sum_parol = g_checksum_new(G_CHECKSUM_MD5);
    g_checksum_update(sum_parol, (guchar *)salted_password, strlen(salted_password));
    const char *hash_parol = g_checksum_get_string(sum_parol);

    // Сохраняется в БД
    if (insert_hash_to_db(login, hash_parol, salt_value) == 0) {
        g_print("Данные сохранены в БД\n");
    } else {
        g_printerr("Не удалось сохранить в БД\n");
    }

    // Очищается память
    g_free(salted_password);
    g_checksum_free(sum_parol);
    g_free(salt_value);
}
