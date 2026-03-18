include ../Makefile.inc

release : main.r.o library.r.o
	$(LD) -o $@ $^

debug   : main.d.o library.d.o
	$(LD) -o $@ $^

utest   : test_main.d.o library.d.o
	$(LD) $(GTEST_LIBS) -o $@ $^

run_utest : utest
	./$^

run_itest : debug
	echo "Integration tests..."
	./$^

include Makefile.hdrdep
