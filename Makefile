all:
	gcc -g `pkg-config --libs --cflags clutter-1.0 clutter-gtk-1.0 json-glib-1.0 gtk+-3.0` gml-gtk-widget.c gml-test.c -o gml
