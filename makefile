all: tudo

tudo:
	-g++ -c ./*/*.h ./*/*.cpp
	-mv ./*/*.gch ./.compiled/
	-mv *.o .compiled/

.PHONY: clean

clean:
	-rm -f -r .compiled/*


