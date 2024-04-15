#include <gtk/gtk.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    // �������� ����
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "������ ���� GTK+");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // �������� ������� ������
    GtkWidget *button = gtk_button_new_with_label("����� ����");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    // �������� ���������� ��� ���������� ������
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(box), button);

    // ���������� ���������� � ����
    gtk_container_add(GTK_CONTAINER(window), box);

    // ����������� ���� ���������
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
