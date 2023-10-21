#include <gtk/gtk.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    // Создание окна
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Пример окна GTK+");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Создание виджета кнопки
    GtkWidget *button = gtk_button_new_with_label("Нажми меня");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    // Создание контейнера для размещения кнопки
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(box), button);

    // Размещение контейнера в окне
    gtk_container_add(GTK_CONTAINER(window), box);

    // Отображение всех элементов
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
