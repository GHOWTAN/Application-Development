OBJ = main.o screen.o sound.o
APPNAME = soundApp

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

%.o : %.c
	gcc -c -o $@ $<

clean :
	rm $(OBJ) $(APPNAME)

pack :
	tar -cvf appdev.tar *.c *.h makefile README
