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
  // * draw cairo primitive: cairo_arc
  double radius = MIN(width, height) / 2.0; // radius (max radius)
  // centered circle
  cairo_arc(cr,                        // cairo renderer
            width / 2.0, height / 2.0, // position x y (centered)
            radius,                    // radius (max radius)
            0, 2 * G_PI);              // full arc is circle (angles: from 0 , to 2*PI )
  // set color then fill color
  GdkRGBA circle_color = {.red = 0, .green = 0, .blue = 0, .alpha = 1}; // black (opaque alpha)
  gdk_cairo_set_source_rgba(cr, &circle_color);                         // set color to fill circle
  cairo_fill(cr);                                                       // cairo renderer that fills circle (full arc)

  // * draw cairo primitive: cairo_rectangle
  int size = radius / 3; // radius/3
  // centered square (even sized rectangle)
  GdkRectangle square =
      {.x = width / 2 - size / 2, .y = height / 2 - size / 2, .width = size, .height = size}; // centered and even sized
  cairo_rectangle(cr, square.x, square.y, square.width, square.height);                       // cairo renderer and xywh
  // set color then fill color
  GdkRGBA square_color = {.red = 1, .green = 1, .blue = 0, .alpha = 1}; // yellow (opaque alpha)
  gdk_cairo_set_source_rgba(cr, &square_color);                         // set color to fill square
  cairo_fill(cr);                                                       // cairo renderer that fills square (even sized rectangle)                                                                                                // fill square (even sized rectangle)
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
