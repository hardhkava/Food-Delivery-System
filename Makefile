CC = gcc
OBJS = admin_ui.o customerUI.o delivery.o restaurantUI.o main.o
EXECS = admin customer delivery restaurant main

all: $(EXECS)

admin: admin_ui.o
	$(CC) $< -o $@

customer: customerUI.o
	$(CC) $< -o $@

delivery: delivery.o
	$(CC) $< -o $@

restaurant: restaurantUI.o
	$(CC) $< -o $@

main: main.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(OBJS) $(EXECS)
