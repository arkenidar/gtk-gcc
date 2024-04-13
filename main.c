// sudo apt install git gcc gdb pkgconf libgtk-4-dev cmake ninja-build
// gcc *.c -o gtk-app `pkg-config --cflags --libs gtk4` && ./gtk-app

// https://docs.gtk.org/gtk4
// https://docs.gtk.org/gtk4/class.DrawingArea.html

#include <gtk/gtk.h>

static void
draw_function(GtkDrawingArea *area,
              cairo_t *cr,
              int width,
              int height,
              gpointer data)
{
  GdkRGBA color;
  GtkStyleContext *context;

  context = gtk_widget_get_style_context(GTK_WIDGET(area));

  cairo_arc(cr,
            width / 2.0, height / 2.0,
            MIN(width, height) / 2.0,
            0, 2 * G_PI);

  gtk_style_context_get_color(context,
                              &color);
  gdk_cairo_set_source_rgba(cr, &color);

  cairo_fill(cr);
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  GtkWidget *area = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 100);
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 100);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area),
                                 draw_function,
                                 NULL, NULL);
  gtk_window_set_child(GTK_WINDOW(window), area);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc,
         char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE); // G_APPLICATION_DEFAULT_FLAGS
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
