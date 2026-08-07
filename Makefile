CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4` -lsqlite3
SRCS = main.c ui.c callbacks.c db.c salt.c
OBJS = $(SRCS:.c=.o)
TARGET = auth_system.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

ui.o: ui.c ui.h
callbacks.o: callbacks.c callbacks.h
db.o: db.c db.h
salt.o: salt.c salt.h
main.o: main.c ui.h db.h
