src = $(wildcard src/*.c)
objdir = $(wildcard obj)
obj = $(src:.c=.o)

LDFLAGS = -lpng -lz -lm


myprog: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)
	mv $(obj) $(objdir)
	
.PHONY: clean
clean:
	rm -f $(obj) myprog
	cd $(objdir) && rm -f *.o