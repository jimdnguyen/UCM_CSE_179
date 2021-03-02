CC_R = xlc_r

TARGETS = test03

OBJS = test03.o

SRCS = $(OBJS:.o=.c)

$(TARGETS): $(OBJS)
	$(CC_R) -o $@ $@.o

clean:
	rm $(OBJS) $(TARGETS)

run:
	test03