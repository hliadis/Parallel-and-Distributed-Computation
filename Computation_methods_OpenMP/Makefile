CC = gcc # you may need to change this, depending on your OS
CFLAGS = -O4 -fopenmp # you may need to change this, depending on your OS
LDFLAGS = -lm # you may need to change this, depending on your OS
 # you may need to change this, depending on your OS
RM = /bin/rm -f
EXE = ask1 ask3 ask2
all: $(EXE)
%: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $< -lm
%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $@ $<
clean:
	$(RM) *.o $(EXE)
