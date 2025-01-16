CC=clang

all:
	mkdir -p libs bin
	${CC} -Wall -c ./src/event_loop.c -o ./libs/lib_event_loop.o
	ar rcs ./libs/lib_event_loop.a ./libs/lib_event_loop.o
	cd ..
	${CC} -I ./libs/ -c ./src/demo_app.c -o ./libs/demo_app.o
	${CC} -o bin/demo_app ./libs/demo_app.o ./libs/lib_event_loop.a

clean:
	rm -rf libs bin
