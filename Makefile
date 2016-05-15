all: client server logger

client:
	cd client; make all imp=$(imp)

server:
	cd server; make all imp=$(imp)

logger:
	cd logger; make all

clean:
	cd client; make clean imp=$(imp)
	cd server; make clean imp=$(imp)

run:
	cd logger; ./logger.bin
	cd server; ./server.bin

.PHONY: client server logger run
