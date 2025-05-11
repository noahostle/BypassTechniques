CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64
LDFLAGS = -shared -Wl,--subsystem,windows



original:clean injector original_dll
ablated: clean injector ablated_dll





original_dll: original_dll.c
	$(CC) $(LDFLAGS) -o payload.dll original_dll.c

ablated_dll: ablated_dll.c
	$(CC) $(LDFLAGS) -o payload.dll ablated_dll.c

injector: injector.c
	$(CC) $(CFLAGS) -o injector.exe injector.c


clean:
	rm -f payload.dll
	rm -f injector.exe
