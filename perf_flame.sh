perf record -a -g ./a.out
perf script|../FlameGraph/./stackcollapse-perf.pl | ../FlameGraph/./flamegraph.pl > kernel.svg
