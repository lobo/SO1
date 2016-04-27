all: client server

client:
	cd client; make all imp=$(imp)

server:
	cd server; make all imp=$(imp)

clean:
	cd client; make clean imp=$(imp)
	cd server; make clean imp=$(imp)

.PHONY: client server
