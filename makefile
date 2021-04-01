all: 
	-g++ -c ./*/*.h ./*/*.cpp
	-mkdir .compiled
	-mv ./*/*.gch ./.compiled/
	-mv *.o .compiled/

.PHONY: clean

clean:
	-rm -f -r .compiled/*

