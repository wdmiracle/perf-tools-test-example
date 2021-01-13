SOURCES := $(wildcard *.c)
TARGETS := $(patsubst %.c, %, $(SOURCES))
OBJS := $(patsubst %.c, %.o, $(SOURCES))

CC := gcc
HIDE := @
RM := rm

all:$(TARGETS)

$(TARGETS): %:%.o
	$(HIDE) $(CC) $< -o $@

$(OBJS): %.o:%.c
	$(HIDE) $(CC) -c $< -o $@

.PHONY:clean
clean:
	$(HIDE) $(RM) -rf $(OBJS) $(TARGETS) *.txt
