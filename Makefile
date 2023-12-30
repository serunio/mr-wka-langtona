CFLAGS += -I../.. -Os -s
WINFLAGS += -lopengl32 -lgdi32
LINFLAGS += -lGLU -lGL -lX11

mrowka : src/main.c src/plansza.c tigr/tigr.c
	x86_64-w64-mingw32-g++ $^ -o exe/$@-win.exe $(CFLAGS) $(WINFLAGS)
	gcc $^ -o exe/$@ $(CFLAGS) $(LINFLAGS)
