INCLUDES = -Iheaders/
SOURCE_FILES = main.c module/init.c module/interface.c
LIBRARIES = -lncurses
BINARY_NAME=network_monitor

clean:
	rm main

compile:
	gcc $(INCLUDES) $(SOURCE_FILES) $(LIBRARIES) -o $(BINARY_NAME)
