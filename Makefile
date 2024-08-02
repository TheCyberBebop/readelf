all: readelf

readelf: readelf.c
	gcc -g readelf.c -o readelf

clean:
	-rm -rf readelf