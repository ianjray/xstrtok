.POSIX:
.SUFFIXES:
.SUFFIXES: .c .unittest .profraw .profdata .coverage

CC         = clang
XCRUN      = xcrun
CPROF      = $(XCRUN) llvm-profdata
CCOV       = $(XCRUN) llvm-cov

SANITIZE   = -fsanitize=address -fsanitize=undefined-trap -fsanitize-undefined-trap-on-error
COVERAGE   = -fprofile-instr-generate -fcoverage-mapping
OPTS       = -Werror -Weverything -Wno-padded -Wno-poison-system-directories

.PHONY: all
all: xstrtok.coverage

xstrtok.unittest: test_xstrtok.c

.profdata.coverage:
	$(CCOV) show $*.unittest -instr-profile=$< $*.c > $@
	! grep " 0|" $@
	echo PASS $@

.profraw.profdata:
	$(CPROF) merge -sparse $< -o $@

.unittest.profraw:
	LLVM_PROFILE_FILE=$@ ./$<

.c.unittest:
	$(CC) $(SANITIZE) $(COVERAGE) $(OPTS) $^ -o $@

.PHONY: clean
clean:
	rm -rf *.coverage *.profdata *.profraw *.unittest*
