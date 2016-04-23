all: clean namedPipes sockets

namedPipes:
	cd namedPipes; make all

sockets:
	cd sockets; make all

clean:
	cd namedPipes; make clean
	cd sockets; make clean