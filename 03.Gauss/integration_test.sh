#!/bin/bash
status=true

cat << 'EOF2' > expected.csv
A,B
-1.000000
2.000000
EOF2

./gauss AB.csv > output.csv

if cmp -s output.csv expected.csv; then
    echo "Integration test: PASSED"
else
    echo "Integration test: FAILED"
    status=false
fi

rm -f expected.csv output.csv
$status
