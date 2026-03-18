include ../Makefile.inc

release    : main.r.o library.r.o
	$(LD) -o $@ $^

debug      : main.d.o library.d.o
	$(LD) -o $@ $^

debug_test : test_main.d.o library.d.o
	$(LD) $(GTEST_LIBS) -o $@ $^

run_debug_test : debug_test
	./$^

include Makefile.hdrdep
