#include <gtk/gtk.h>
#include <stdlib.h>

#include "gml.h"


int
main (int argc, char *argv[])
{
    GtkWidget *window = NULL;
    GtkWidget *gml_widget = NULL;

    //gtk_init (&argc, &argv);
    gtk_clutter_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    gml_widget = gml_gtk_widget_new_from_file ("main.gml");

    gtk_container_add (GTK_CONTAINER (window), gml_widget);

    gtk_widget_show_all (window);
    gtk_main ();

    return EXIT_SUCCESS;
}
