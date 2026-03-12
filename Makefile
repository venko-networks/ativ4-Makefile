TARGET = elsys_app
CC = gcc
CFLAGS = -Wall
# Adicionada a libcrypto (OpenSSL)
LDFLAGS = -lpthread -lcrypto 

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LDFLAGS)

install:
	install -d $(DESTDIR)/usr/bin
	install -m 0755 $(TARGET) $(DESTDIR)/usr/bin
