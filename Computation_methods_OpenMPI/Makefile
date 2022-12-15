CC = mpicc # you may need to change this, depending on your OS
RM = /bin/rm -f
EXE = ask1 ask2 ask3
all: $(EXE)
%: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $< -lm
%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $@ $<
clean:
	$(RM) *.o $(EXE)
