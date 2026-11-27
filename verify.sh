#!/bin/sh
set -eu

# Rebuild both certificates from the order-23 matrices, compare them with the shipped
# files and their pinned SHA-256 digests, then check the shipped files with the separate
# verifier. With an argument, keep the outputs in a fresh subdirectory of that directory.
parent=${1:-${TMPDIR:-/tmp}}
mkdir -p "$parent"
out=$(mktemp -d "$parent/hadamard-4792.XXXXXX")
root=$(CDPATH= cd "$(dirname "$0")" && pwd)
src="$root/evidence"
CXX=${CXX:-c++}

sha256() {
    if command -v shasum >/dev/null 2>&1; then shasum -a 256 "$1" | cut -d' ' -f1
    else sha256sum "$1" | cut -d' ' -f1; fi
}
pin() {
    actual=$(sha256 "$1")
    if [ "$actual" != "$2" ]; then echo "SHA-256 MISMATCH for $1: $actual" >&2; exit 1; fi
    echo "MATCH $3 $actual"
}

"$CXX" -O3 -std=c++17 "$src/build.cpp" -o "$out/build"
"$CXX" -O3 -std=c++17 "$src/verify.cpp" -o "$out/verify"
"$CXX" -O3 -std=c++17 -I "$src" "$src/universal.cpp" -o "$out/universal"

"$out/build" "$src/wt23.txt" "$out/sh598.sp2" "$out/H4792.packed"
pin "$out/sh598.sp2" a7e2e4ce8b817cb281c8cd95268939d64242177e78923714134c66ac508ce217 "rebuilt sh598.sp2"
pin "$out/H4792.packed" a92ec95ed93df69d68685818dbe191a7021af4bf4bccdd8f179d9c12d32cc59a "rebuilt H4792.packed"

cmp "$out/sh598.sp2" "$src/sh598.sp2"
gzip -dc "$src/H4792.packed.gz" > "$out/shipped-H4792.packed"
cmp "$out/H4792.packed" "$out/shipped-H4792.packed"
echo "MATCH rebuilt files equal the shipped evidence/sh598.sp2 and evidence/H4792.packed.gz"

"$out/verify" "$src/sh598.sp2" "$out/shipped-H4792.packed"

# Exhaustive pairing search on the order-52 array: none works for four independent
# variables; with x1 = x2 the search must find the pairing used above.
"$out/universal" | tee "$out/universal.txt"
"$out/universal" merge12 | tee -a "$out/universal.txt"
grep -q '^independent variables: no pairing exists' "$out/universal.txt"
grep -q '^x1 = x2: a pairing exists' "$out/universal.txt"
echo "MATCH pairing search"
echo "Outputs and programs in $out"
