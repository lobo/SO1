all: client server

client:
	cd client; make all

server:
	cd server; make all

clean:
	cd client; make clean
	cd server; make clean
	rm /tmp/*_r
	rm /tmp/*_w

.PHONY: client server
