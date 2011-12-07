#include <clutter-gtk/clutter-gtk.h>

#include <glib-object.h>
#include <json-glib/json-glib.h>

#include "gml-gtk-widget.h"

G_DEFINE_TYPE (GmlGtkWidget, gml_gtk_widget, GTK_TYPE_GRID);

// static

static void
gml_gtk_widget_create_rect (ClutterActor *parent, JsonObject *obj)
{
    GList *l = NULL;
    GList *p = NULL;
    ClutterColor color = { 0x00, 0x00, 0x00, 0xff };
    ClutterActor *rect = clutter_rectangle_new ();

    l = json_object_get_members (obj);

    for (p = l; p; p = p->next) {
        if (!strcmp (p->data, "width")) {
            clutter_actor_set_width (rect, (float)json_object_get_int_member (obj, p->data));
        } else if (!strcmp (p->data, "height")) {
            clutter_actor_set_height (rect, (float)json_object_get_int_member (obj, p->data));
        } else if (!strcmp (p->data, "x")) {
            clutter_actor_set_x (rect, (float)json_object_get_int_member (obj, p->data));
        } else if (!strcmp (p->data, "y")) {
            clutter_actor_set_y (rect, (float)json_object_get_int_member (obj, p->data));
        } else if (!strcmp (p->data, "color")) {
            clutter_color_from_string (&(color), json_object_get_string_member (obj, p->data));
            clutter_rectangle_set_color (CLUTTER_RECTANGLE (rect), &color);
        } else if (!strcmp (p->data, "border.width")) {
            clutter_rectangle_set_border_width (CLUTTER_RECTANGLE (rect), json_object_get_int_member (obj, p->data));
        } else if (!strcmp (p->data, "border.color")) {
            clutter_color_from_string (&(color), json_object_get_string_member (obj, p->data));
            clutter_rectangle_set_border_color (CLUTTER_RECTANGLE (rect), &color);
        }
    }

    clutter_container_add_actor (CLUTTER_CONTAINER (parent), rect);
}

static void
gml_gtk_widget_create_element (ClutterActor *parent, JsonObject *obj)
{
    const gchar *klass = json_object_get_string_member (obj, "class");
    if (!strcmp (klass, "Rectangle")) {
        gml_gtk_widget_create_rect (parent, obj);
    }
}

// end of static

GtkWidget *
gml_gtk_widget_new ()
{
    GtkWidget *obj;

    obj = g_object_new (GML_TYPE_GTK_WIDGET, NULL);

    GmlGtkWidget *gml = GML_GTK_WIDGET (obj);
    GtkGrid *grid = GTK_GRID (obj);

    gml->clutter_widget = gtk_clutter_embed_new ();
    gtk_widget_set_size_request (gml->clutter_widget, gml->width, gml->height);
    gml->stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (gml->clutter_widget));
    clutter_stage_set_color (CLUTTER_STAGE (gml->stage), &(gml->stage_color));
    clutter_actor_show (gml->stage);

    gtk_widget_set_vexpand (gml->clutter_widget, TRUE);
    gtk_widget_set_valign (gml->clutter_widget, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand (gml->clutter_widget, TRUE);
    gtk_widget_set_halign (gml->clutter_widget, GTK_ALIGN_FILL);

    gtk_grid_attach (grid, gml->clutter_widget, 0, 0, 1, 1);

    return obj;
}

GtkWidget *
gml_gtk_widget_new_from_file (gchar *f)
{
    GmlGtkWidget *widget = GML_GTK_WIDGET (gml_gtk_widget_new ());
    gml_gtk_widget_set_file (widget, f);
    return GTK_WIDGET (widget);
}

void
gml_gtk_widget_set_source (GmlGtkWidget *gml, gchar *source)
{
    // TODO set source to gml
}

void
gml_gtk_widget_set_file (GmlGtkWidget *gml, gchar *f)
{
    JsonParser *parser = NULL;
    JsonNode *node = NULL;
    JsonObject *obj = NULL;
    JsonArray *arr = NULL;
    GError *error = NULL;
    GList *l = NULL;
    GList *p = NULL;

    parser = json_parser_new ();
    json_parser_load_from_file (parser, f, &error);
    if (error) {
        g_print ("Unable to parse `%s': %s\n", f, error->message);
        g_error_free (error);
        g_object_unref (parser);
        return;
    }

    node = json_parser_get_root (parser);
    obj = json_node_get_object (node);
    l = json_object_get_members (obj);

    for (p = l; p; p = p->next) {
        if (!strcmp (p->data, "width")) {
            gml->width = json_object_get_int_member (obj, p->data);
        } else if (!strcmp (p->data, "height")) {
            gml->height = json_object_get_int_member (obj, p->data);
        } else if (!strcmp (p->data, "color")) {
            clutter_color_from_string (&(gml->stage_color),
                    json_object_get_string_member (obj, p->data));
        } else if (!strcmp (p->data, "elements")) {
            GList *al = NULL;
            GList *ap = NULL;
            JsonObject *arro = NULL;
            // parsing elements
            arr = json_object_get_array_member (obj, p->data);
            al = json_array_get_elements (arr);
            for (ap = al; ap; ap = ap->next) {
                arro = json_node_get_object (ap->data);
                gml_gtk_widget_create_element (gml->stage, arro);
            }

        }
    }

    g_list_free (l);
    g_object_unref (parser);

    gtk_widget_set_size_request (gml->clutter_widget, gml->width, gml->height);
    clutter_stage_set_color (CLUTTER_STAGE (gml->stage), &(gml->stage_color));
}

static void
gml_gtk_widget_init (GmlGtkWidget *self)
{
}

static void
gml_gtk_widget_class_init (GmlGtkWidgetClass *klass)
{
}
