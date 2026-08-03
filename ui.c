#include "ui.h"
#include "callbacks.h"
#include "db.h"

void activate(GtkApplication *app, gpointer user_data) {
    // Инициализация базы данных
    if (init_database("hashes.db") != 0) {
        g_printerr("Критическая ошибка БД, приложение завершается\n");
        return;
    }

    // Загружается CSS для стилизации
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(css_provider,
        // Стили для заголовка окна
        "headerbar {"
        "   background: rgba(22, 41, 56, 0.95);"
        "   color: #ffffff;"
        "   border-bottom: 2px solid rgba(255, 255, 255, 0.2);"
        "   min-height: 40px;"
        "   padding: 0 10px;"
        "}"
        "headerbar button {"
        "   background: transparent;"
        "   color: #ffffff;"
        "   border: 1px solid transparent;"
        "   border-radius: 6px;"
        "   padding: 4px 8px;"
        "   margin: 2px;"
        "}"
        "headerbar button:hover {"
        "   background: rgba(255, 255, 255, 0.2);"
        "   border-color: rgba(255, 255, 255, 0.3);"
        "   color: #ffffff;"
        "}"
        "headerbar button.close {"
        "   background: transparent;"
        "}"
        "headerbar button.close:hover {"
        "   background: #e81123;"
        "   color: #ffffff;"
        "}"
        "headerbar label {"
        "   color: #ffffff;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   text-shadow: none;"
        "}"
        // Стили для заголовка окна
        "titlebar {"
        "   background: rgba(22, 41, 56, 0.95);"
        "   color: #ffffff;"
        "}"
        "titlebar button {"
        "   background: transparent;"
        "   color: #ffffff;"
        "   border: 1px solid transparent;"
        "   border-radius: 6px;"
        "   padding: 4px 8px;"
        "   margin: 2px;"
        "}"
        "titlebar button:hover {"
        "   background: rgba(255, 255, 255, 0.2);"
        "   border-color: rgba(255, 255, 255, 0.3);"
        "   color: #ffffff;"
        "}"
        "titlebar label {"
        "   color: #ffffff;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   text-shadow: none;"
        "}"
        // Основные стили для меток
        "label {"
        "   color: #1a1a2e;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        // Стиль для заголовка карточки
        "#card_title {"
        "   color: #162938;"
        "   font-size: 26px;"
        "   font-weight: 900;"
        "   text-shadow: none;"
        "   letter-spacing: 1px;"
        "}"
        "#card_subtitle {"
        "   color: #5a6c7d;"
        "   font-size: 14px;"
        "   font-weight: 400;"
        "   text-shadow: none;"
        "   margin-bottom: 10px;"
        "}"
        // Стили для полей ввода
        "entry {"
        "   background: #ffffff;"
        "   border: 2px solid #c0c9d1;"
        "   border-radius: 10px;"
        "   color: #162938;"
        "   font-size: 15px;"
        "   font-weight: 500;"
        "   padding: 14px 16px;"
        "   margin: 5px 0;"
        "   box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);"
        "   transition: all 0.3s ease;"
        "}"
        "entry:focus {"
        "   background: #ffffff;"
        "   border-color: #162938;"
        "   box-shadow: 0 0 0 4px rgba(22, 41, 56, 0.15), 0 2px 8px rgba(0, 0, 0, 0.1);"
        "   outline: none;"
        "}"
        "entry:disabled {"
        "   background: #f0f2f5;"
        "   border-color: #d0d5dc;"
        "   color: #8a96a4;"
        "}"
        "entry selection {"
        "   background: #162938;"
        "   color: #ffffff;"
        "}"
        "entry text {"
        "   background: transparent;"
        "   color: #162938;"
        "   font-weight: 500;"
        "}"
        // Цвет ввода текста
        "entry placeholder {"
        "   color: #162938;"
        "   font-weight: 400;"
        "   font-style: italic;"
        "}"
        // Стиль для кнопки с глазиком
        "#eye_button {"
        "   background: #ffffff;"
        "   border: 2px solid #c0c9d1;"
        "   border-radius: 10px;"
        "   padding: 8px;"
        "   margin: 5px 0;"
        "   min-width: 42px;"
        "   min-height: 42px;"
        "   color: #5a6c7d;"
        "   transition: all 0.3s ease;"
        "}"
        "#eye_button:hover {"
        "   background: #f8f9fa;"
        "   color: #162938;"
        "   border-color: #162938;"
        "   box-shadow: 0 2px 8px rgba(22, 41, 56, 0.15);"
        "}"
        "#eye_button image {"
        "   color: #5a6c7d;"
        "}"
        "#eye_button:hover image {"
        "   color: #162938;"
        "}"
        // Основной стиль для кнопок
        "button {"
        "   background: #162938;"
        "   color: #ffffff;"
        "   border: 2px solid #162938;"
        "   border-radius: 10px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 14px;"
        "   margin-top: 15px;"
        "   transition: all 0.3s ease;"
        "   box-shadow: 0 4px 12px rgba(22, 41, 56, 0.2);"
        "}"
        "button:hover {"
        "   background: #1a3346;"
        "   color: #ffffff;"
        "   border-color: #1a3346;"
        "   box-shadow: 0 6px 16px rgba(22, 41, 56, 0.3);"
        "   transform: translateY(-1px);"
        "}"
        "button:active {"
        "   transform: translateY(0);"
        "   box-shadow: 0 2px 8px rgba(22, 41, 56, 0.2);"
        "}"
        "button label {"
        "   color: #ffffff;"
        "   text-shadow: none;"
        "   font-size: 18px;"
        "}"
        "button:hover label {"
        "   color: #ffffff;"
        "}"
        // Стиль для кнопки Войти
        "#login_button {"
        "   border-radius: 25px;"
        "   padding: 16px 35px;"
        "   font-size: 17px;"
        "   min-height: 48px;"
        "   letter-spacing: 1px;"
        "   font-weight: 900;"
        "}"
        "#login_button label {"
        "   font-size: 17px;"
        "   font-weight: 900;"
        "}"
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    // Создание окна
    GtkWidget *win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Система авторизации");
    gtk_window_set_default_size(GTK_WINDOW(win), 450, 280);

    // Центрирование окна в GTK4
    gtk_window_set_gravity(GTK_WINDOW(win), GDK_GRAVITY_CENTER);

    // Создание headerbar для кастомного заголовка
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header), TRUE);
    gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header), gtk_label_new("Система авторизации"));
    gtk_window_set_titlebar(GTK_WINDOW(win), header);

    // Создание оверлей
    GtkWidget *overlay = gtk_overlay_new();
    gtk_window_set_child(GTK_WINDOW(win), overlay);

    // Создание и настраивание фоновой картинки
    GtkWidget *background = gtk_picture_new_for_filename("bg.jpg");

    // Устанавливается content fit для растягивания
    gtk_picture_set_content_fit(GTK_PICTURE(background), GTK_CONTENT_FIT_FILL);

    // Растягивается на весь размер родителя
    gtk_widget_set_hexpand(background, TRUE);
    gtk_widget_set_vexpand(background, TRUE);

    // Устанавливается как основной (задний) слой оверлея
    gtk_overlay_set_child(GTK_OVERLAY(overlay), background);

    // Создаём CenterBox для центрирования карточки
    GtkWidget *center_box = gtk_center_box_new();
    gtk_widget_set_hexpand(center_box, TRUE);
    gtk_widget_set_vexpand(center_box, TRUE);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), center_box);

    // Создаём карточку авторизации
    GtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(card, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(card, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(card, 440, -1);

    // Устанавливаем карточку как центральный виджет CenterBox
    gtk_center_box_set_center_widget(GTK_CENTER_BOX(center_box), card);

    // Добавляется фон для карточки
    GtkWidget *card_background = gtk_frame_new(NULL);
    gtk_widget_set_name(card_background, "content_frame");
    gtk_box_append(GTK_BOX(card), card_background);

    // Создаётся CSS для фрейма с улучшенной видимостью
    GtkCssProvider *frame_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(frame_provider,
        "#content_frame {"
        "   background: rgba(255, 255, 255, 0.92);"
        "   border-radius: 20px;"
        "   padding: 20px;"
        "   box-shadow: 0 10px 40px rgba(0, 0, 0, 0.2), 0 0 0 1px rgba(255, 255, 255, 0.1);"
        "}"
    );
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(frame_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    // Основной контейнер внутри фрейма
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_frame_set_child(GTK_FRAME(card_background), box);
    gtk_widget_set_margin_top(box, 30);
    gtk_widget_set_margin_bottom(box, 30);
    gtk_widget_set_margin_start(box, 30);
    gtk_widget_set_margin_end(box, 30);

    // ЗАГОЛОВОК КАРТОЧКИ
    GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_halign(title_box, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_bottom(title_box, 20);
    gtk_box_append(GTK_BOX(box), title_box);

    // Главный заголовок
    GtkWidget *card_title = gtk_label_new("Добро пожаловать");
    gtk_widget_set_name(card_title, "card_title");
    gtk_label_set_justify(GTK_LABEL(card_title), GTK_JUSTIFY_CENTER);
    gtk_box_append(GTK_BOX(title_box), card_title);

    // Подзаголовок
    GtkWidget *card_subtitle = gtk_label_new("Войдите в свою учётную запись");
    gtk_widget_set_name(card_subtitle, "card_subtitle");
    gtk_label_set_justify(GTK_LABEL(card_subtitle), GTK_JUSTIFY_CENTER);
    gtk_box_append(GTK_BOX(title_box), card_subtitle);

    // Разделитель
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_margin_bottom(separator, 10);
    gtk_box_append(GTK_BOX(box), separator);

    // Поле логина
    GtkWidget *login_label = gtk_label_new("Логин:");
    gtk_widget_set_halign(login_label, GTK_ALIGN_START);
    gtk_widget_set_margin_bottom(login_label, 2);
    gtk_box_append(GTK_BOX(box), login_label);

    GtkWidget *login_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_entry), "Введите логин...");
    gtk_box_append(GTK_BOX(box), login_entry);

    // Сохраняется указатель на поле логина для callback-функций
    set_login_entry(login_entry);

    // Поле пароля
    GtkWidget *password_label = gtk_label_new("Пароль:");
    gtk_widget_set_halign(password_label, GTK_ALIGN_START);
    gtk_widget_set_margin_top(password_label, 5);
    gtk_widget_set_margin_bottom(password_label, 2);
    gtk_box_append(GTK_BOX(box), password_label);

    GtkWidget *password_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_box_append(GTK_BOX(box), password_box);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Введите пароль...");
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_box_append(GTK_BOX(password_box), entry);

    // Кнопка с глазиком
    GtkWidget *eye_btn = gtk_button_new_from_icon_name("view-conceal-symbolic");
    gtk_widget_set_name(eye_btn, "eye_button");
    gtk_widget_set_size_request(eye_btn, 42, 42);
    g_signal_connect(eye_btn, "clicked", G_CALLBACK(toggle_visibility), entry);
    gtk_box_append(GTK_BOX(password_box), eye_btn);

    // Кнопка входа
    GtkWidget *btn = gtk_button_new_with_label("Войти");
    gtk_widget_set_name(btn, "login_button");
    gtk_widget_set_margin_top(btn, 5);
    gtk_box_append(GTK_BOX(box), btn);

    // Метки результатов
    GtkWidget *result_login = gtk_label_new("");
    gtk_label_set_selectable(GTK_LABEL(result_login), TRUE);
    gtk_widget_set_margin_top(result_login, 5);
    gtk_box_append(GTK_BOX(box), result_login);

    GtkWidget *result_parol = gtk_label_new("");
    gtk_label_set_selectable(GTK_LABEL(result_parol), TRUE);
    gtk_box_append(GTK_BOX(box), result_parol);

    // Сохраняются указатели на метки для callback-функций
    set_result_widgets(result_login, result_parol);

    // Подключение сигнала кнопки
    g_signal_connect(btn, "clicked", G_CALLBACK(hash_clicked), entry);

    // Делаем окно на весь экран
    gtk_window_maximize(GTK_WINDOW(win));

    gtk_window_present(GTK_WINDOW(win));
}
