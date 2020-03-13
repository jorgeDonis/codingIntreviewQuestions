all:
	gcc -g -Wall `pkg-config --cflags --libs glib-2.0` questions.c -o questions

	