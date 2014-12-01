/*
 * g++ `pkg-config --cflags --libs gtk+-2.0` ts-gtk.cpp -o ts-gtk
 */

#include <gtk/gtk.h>
#include <iostream>

gboolean hello(GtkWidget* sender, GdkEventConfigure *event)
{
	std::cout << "[1] hello \n";

	return true;
}

std::string buffer(">");

gboolean timer_cb(gpointer data)
{
	static int c = 0;
	std::cout << "hello timer " << c++ << '\n';
	hello(0, 0);

	return true;
}
gboolean hello1(GtkWidget* sender, GdkEventConfigure *event)
{
	std::cout << "[1] intermedium hello\n";
	return true;
}

gboolean idle_cb(GtkWidget* img1/*sender*/, GdkEventExpose *event)
{
	std::cout << "[0] idle  \n";

	GdkPixbuf *pbuf1 = gdk_pixbuf_new_from_file("./wa.jpg", 0);
//	guchar *pixel1 = gdk_pixbuf_get_pixels(pbuf1);

	if (!pbuf1) return 0;


//	GdkPixbuf *pbuf2 = gdk_pixbuf_new(GDK_COLORSPACE_RGB, false, 8, 100, 132);
//	gdk_pixbuf_composite(pbuf1, pbuf1, 
//		0, 132-90, 
//		100, 90, 
//		0, 0, 0, 132, 
//		GDK_INTERP_BILINEAR, 255);

	gdk_draw_pixbuf(
		img1->window,
		img1->style->black_gc,//fg_gc[GTK_WIDGET_STATE(img1)],
		pbuf1, 
		0, 0, 0, 0,
		gdk_pixbuf_get_width(pbuf1),
		gdk_pixbuf_get_height(pbuf1),
		GDK_RGB_DITHER_NORMAL,
		100, 132);

//
////--------------------------
//	for (int i = 1; i < 6; i++)
//	{
//	GdkPixbuf *pbuf2 = gdk_pixbuf_rotate_simple(pbuf1, (GdkPixbufRotation)(90*i));//GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE);
//
//	gdk_draw_pixbuf(
//		img1->window,
//		img1->style->black_gc,//fg_gc[GTK_WIDGET_STATE(img1)],
//		pbuf2, 
//		0, 0,
//		gdk_pixbuf_get_width(pbuf1)*(i-1),
//		gdk_pixbuf_get_height(pbuf1),
//		gdk_pixbuf_get_width(pbuf1),
//		gdk_pixbuf_get_height(pbuf1),
//		GDK_RGB_DITHER_NORMAL,
//		102, 102);
//	}
////--------------------------
////	pbuf1 = gdk_pixbuf_rotate_simple(pbuf1, GDK_PIXBUF_ROTATE_UPSIDEDOWN);
//	int offset = 0;
//	for (int i = 255; i >100; i -= 20)
//	{
//		pbuf1 = gdk_pixbuf_add_alpha(pbuf1, true, i, i, i);
//
//		gdk_draw_pixbuf(
//		img1->window,
//		img1->style->fg_gc[GTK_WIDGET_STATE(img1)],
//		pbuf1,
//		0, 0,
//		gdk_pixbuf_get_width(pbuf1)*offset++,
//		gdk_pixbuf_get_height(pbuf1)*2,
//		gdk_pixbuf_get_width(pbuf1),
//		gdk_pixbuf_get_height(pbuf1),
//		GDK_RGB_DITHER_NORMAL,
//		30, 30);
//	}
////gdk_threads_leave();
//	GdkGC *gc1 = gdk_gc_new(img1->window);
//	GdkColor black;
//	black.red = 231;
//	black.green = 210;
//	black.blue = 111;
//
//	gdk_gc_set_foreground(gc1, &black);
////	black.blue = 0;
////	gdk_gc_set_background(gc1, &black);
////	GdkSegment segs1;
////	segs1.x1 = gdk_pixbuf_get_width(pbuf1)*3;
////	segs1.y1 = gdk_pixbuf_get_height(pbuf1)*3;
////	segs1.x2 = 500;
////	segs1.y2 = 500;
////	gdk_draw_segments(img1->window, gc1, &segs1, 20);
//
//	gdk_draw_arc(img1->window, gc1, false,//true,
//		gdk_pixbuf_get_width(pbuf1),
//		gdk_pixbuf_get_height(pbuf1)*3,
//		250, 100,
//		-30*60, -135*60);
	g_object_unref(pbuf1);
	return true;
}

static GRecMutex my_gdk_lock;

static void my_gdk_lock_enter() {
//	g_print("hello lock\n");
	g_rec_mutex_lock(&my_gdk_lock);
}
static void my_gdk_lock_leave() {g_rec_mutex_unlock(&my_gdk_lock);
}

#include <pthread.h>
#include <iomanip>

gboolean idle_cb1(GtkWidget* img1/*sender*/, GdkEventExpose *event)
{
	std::cout << "[1] intermedium idle \n";

	GdkPixbuf *pbuf1 = gdk_pixbuf_new_from_file("./wa.jpg", 0);

	if (!pbuf1) return 0;
	GdkColor black;
	black.red = 201;
	black.green = 22;
	black.blue = 100;

	GdkGC *gc1 = gdk_gc_new(img1->window);
	gdk_gc_set_background(gc1, &black);
	gdk_gc_set_foreground(gc1, &black);
	g_object_unref(gc1);

	for (int i = 0; i < 9; i++)
	gdk_draw_pixbuf(
		img1->window,
		img1->style->bg_gc[GTK_WIDGET_STATE(img1)],
		pbuf1, 
		0, 0, 80*(i), 0,
		gdk_pixbuf_get_width(pbuf1),
		gdk_pixbuf_get_height(pbuf1),
		GDK_RGB_DITHER_NORMAL,
		102, 102);

	for (int i = 2; i < 5; i++)
	gdk_draw_pixbuf(
		img1->window,
		img1->style->bg_gc[GTK_WIDGET_STATE(img1)],
		pbuf1, 
		0, 0, 100*i, 100*(i+1),
		gdk_pixbuf_get_width(pbuf1),
		gdk_pixbuf_get_height(pbuf1),
		GDK_RGB_DITHER_NORMAL,
		102, 102);
 
	std::cout << "[1] " << std::setw(50) << buffer << '\n';

	return true;
}

bool run = false;

void* thread_func_inside(void *data)
{
	while(run)
	{
		std::cout << "[2] ... ... ... ... ... run ... ... ... ... ... \n";

		if (buffer[0] == '<')
			buffer.erase(buffer.size()-1, 1);
		else if (5 < buffer.size())
			buffer.replace(0, buffer.size(), buffer.size(), '<');
		else
			buffer += ">";
//		std::cout.seekp(100,  std::ios_base::beg);
		sleep(1);
	}
}

gboolean quit_inside(gpointer data)
{
	run = false;
	std::cout << "[2] ... ... ... ... ... off duty ... ... ... ... ... \n";
	return false;
}

void* thread_func(void *data)
{
	gdk_threads_enter();

	//----------------------------
	GtkWidget *parent = GTK_WIDGET(data);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window, 700, 700);
	gtk_window_move(GTK_WINDOW(window), 0, 0);
//	gtk_window_set_transient_for(GTK_WINDOW(parent), GTK_WINDOW(window));
//	gtk_window_set_modal(GTK_WINDOW(parent), true);

	GtkWidget *fixed1 = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed1);

	GtkWidget *img1 = gtk_drawing_area_new();
	GdkColor black;
	black.red = 201;
	black.green = 22;
	black.blue = 100;

	gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &black);
	gtk_widget_modify_bg(img1, GTK_STATE_NORMAL, &black);
	gtk_widget_set_size_request(img1, 650, 650);
	gtk_fixed_put(GTK_FIXED(fixed1), img1, 25, 25);

	g_signal_connect(img1, "configure-event", G_CALLBACK(hello1), img1);
	g_signal_connect(img1, "expose-event", G_CALLBACK(idle_cb1), img1);
	g_signal_connect(window, "destroy", G_CALLBACK(quit_inside), 0);
	gtk_widget_show_all(window);	

	gdk_threads_leave();
}

void start_medium(gpointer data)
{
	pthread_t thr1;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	int thr1_id = pthread_create(&thr1, &attr,
			&thread_func, data);
//------------------------------
	run = true;
	pthread_t thr2;

	int thr1_id_inside = pthread_create(&thr2, &attr,
			&thread_func_inside, data);
}

int main(int argc, char *argv[])
{
	g_rec_mutex_init(&my_gdk_lock);
	gdk_threads_set_lock_functions(G_CALLBACK(my_gdk_lock_enter),
	                         G_CALLBACK(my_gdk_lock_leave));
	gdk_threads_init();

	GtkWidget *window;
	GtkWidget *fixed1 = gtk_fixed_new();

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_move(GTK_WINDOW(window), 0, 0);
	gtk_container_add(GTK_CONTAINER(window), fixed1);

	GtkWidget *btn1 = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(btn1), "enter");
	gtk_widget_set_size_request(btn1, 200, 200);
	g_signal_connect(btn1, "clicked", G_CALLBACK(start_medium), window);
	gtk_fixed_put(GTK_FIXED(fixed1), btn1, 500, 500);
	
	GtkWidget *img1 = gtk_drawing_area_new();
	GdkColor black;
	black.red = 0;
	black.green = 0;
	black.blue = 0;
	gtk_widget_modify_bg(img1, GTK_STATE_NORMAL, &black);
	gtk_widget_set_size_request(img1, 500, 500);
	gtk_fixed_put(GTK_FIXED(fixed1), img1, 0, 0);
	gtk_widget_set_tooltip_text(btn1, "enter me please !");

	g_signal_connect(img1, "configure-event", G_CALLBACK(hello), img1);
	g_signal_connect(img1, "expose-event", G_CALLBACK(idle_cb), img1);
	g_signal_connect(window, "destroy", gtk_main_quit, 0);

	gtk_widget_show_all(window);
	gtk_main();
	std::cout << "[0] leaving ... \n";

	return 0;
}
