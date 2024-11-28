CC=gcc
OBJS=customer_UI.o restowner_UI.o delivery_UI.o
EXECS=customer restowner delivery

all: $(EXECS)

customer: customer_UI.o
	$(CC) $< -o $@

restowner: restowner_UI.o
	$(CC) $< -lm -o $@

delivery: delivery_UI.o
	$(CC) $< -lm -o $@

%.o: %.c
	$(CC) -c $< -lm

clean:
	rm -f $(OBJS) $(EXECS)
