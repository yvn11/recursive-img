/*
 * btn-case.cpp
 *
 * Author: Zex <top_zlynch@yahoo.com>
 *
 * g++ `pkg-config --cflags --libs gtk+-2.0` btn-case.cpp -o btn-case
 */

#include <gtk/gtk.h>
#include <iostream>

void button_clicked(gpointer *wid)
{
        std::cout << "enter-------------\n";
//	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wid), true);
    int b = 0;
    if ((b = gtk_container_get_border_width(GTK_CONTAINER(wid))) != 10)
    {
        std::cout << "border----" << b << "---------\n";
        gtk_container_set_border_width(GTK_CONTAINER(wid), 10);
	GdkColor black;
	black.red = 0;
	black.green = 0;
	black.blue = 0;
		gtk_widget_modify_bg(GTK_WIDGET(wid), GTK_STATE_NORMAL, &black);
    }
    else
    {
        gtk_container_set_border_width(GTK_CONTAINER(wid), 0);
	GdkColor black;
	black.red = 251;
	black.green = 123;
	black.blue = 221;
		gtk_widget_modify_bg(GTK_WIDGET(wid), GTK_STATE_NORMAL, &black);
    }
        std::cout << "leave-------------\n";
}

int main(int argc, char *argv[])
{
	gdk_threads_init();
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *fixed1 = gtk_fixed_new();

	gtk_window_move(GTK_WINDOW(window), 0, 0);
	gtk_container_add(GTK_CONTAINER(window), fixed1);

    GtkWidget *btns[10];

    for (size_t i = 0; i < 10; i++)
    {
        btns[i] = gtk_button_new();
	    GtkWidget *image = 
        gtk_image_new_from_file("./wa.jpg");
		gtk_button_set_image(GTK_BUTTON(btns[i]), image);
	    gtk_widget_set_size_request(btns[i], 120, 120);
    	g_signal_connect(G_OBJECT(btns[i]), "clicked", G_CALLBACK(button_clicked), window);
	    gtk_fixed_put(GTK_FIXED(fixed1), btns[i], 120*i, 0);
    }
	
	g_signal_connect(window, "destroy", gtk_main_quit, 0);

	gtk_widget_show_all(window);
	gtk_main();
	std::cout << "[0] leaving ... \n";

	return 0;
}
