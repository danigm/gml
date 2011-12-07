#ifndef _GML_GTK_WIDGET_H
#define _GML_GTK_WIDGET_H

#include <gtk/gtk.h>
#include <glib-object.h>
#include <clutter/clutter.h>

#define GML_TYPE_GTK_WIDGET            (gml_gtk_widget_get_type ())
#define GML_GTK_WIDGET(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GML_TYPE_GTK_WIDGET, GmlGtkWidget))
#define GML_IS_GTK_WIDGET(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GML_TYPE_GTK_WIDGET))
#define GML_GTK_WIDGET_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GML_TYPE_GTK_WIDGET, GmlGtkWidgetClass))
#define GML_IS_GTK_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GML_TYPE_GTK_WIDGET))
#define GML_GTK_WIDGET_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GML_TYPE_GTK_WIDGET, GmlGtkWidgetClass))

typedef struct _GmlGtkWidget    GmlGtkWidget;
typedef struct _GmlGtkWidgetClass GmlGtkWidgetClass;

struct _GmlGtkWidget {
    GtkGrid parent;

    /* instance members */
    GtkWidget *clutter_widget;
    ClutterActor *stage;

    gint width;
    gint height;
    ClutterColor stage_color;
};

struct _GmlGtkWidgetClass {
    GtkGridClass parent_class;

    /* class members */
};

GType gml_gtk_widget_get_type (void);

/*
 * Method definitions.
 */

GtkWidget * gml_gtk_widget_new ();
GtkWidget * gml_gtk_widget_new_from_file (gchar *f);
void gml_gtk_widget_set_file (GmlGtkWidget *gml, gchar *f);
void gml_gtk_widget_set_source (GmlGtkWidget *gml, gchar *source);

#endif
