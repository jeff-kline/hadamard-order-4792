# Verification record

## Reproduction

From the repository root run `make verify` and `make paper`. Optionally run `make source`, which downloads Maksimović's data file.

| Step | Program | Outcome on November 27, 2026 |
|---|---|---|
| Order-23 quadruple $S,S,I+R,R-I$ | `evidence/build.cpp` | symmetric, pairwise commuting, summed Gram $92I$ |
| Order-52 array | `evidence/build.cpp` | formal Gram $13(x_1^2+x_2^2+x_3^2+x_4^2)I$; 676 paired blocks with sign product $-1$, 572 with every variable even and 104 with $x_1,x_2$ odd |
| Paired-block matrix of order 1196 | `evidence/build.cpp` | all 357,604 blocks Hadamard; 98,306 are reflections times $H_2$ |
| Theorem 1 at $m=599$ | `evidence/build.cpp` | complementary supports, constant strand sums, sign border; matrix of order 4792 written |
| Rebuilt certificates | `verify.sh` | SHA-256 of `sh598.sp2` = `a7e2e4ce8b817cb281c8cd95268939d64242177e78923714134c66ac508ce217`; of `H4792.packed` = `a92ec95ed93df69d68685818dbe191a7021af4bf4bccdd8f179d9c12d32cc59a`; both equal the shipped files |
| $SH(598,SP_2)$ | `evidence/verify.cpp` | $MM^{\mathsf T}=598I$ on 715,806 row pairs; expansion by $H_2$ Hadamard of order 1196 |
| Hadamard matrix of order 4792 | `evidence/verify.cpp` | 11,479,236 distinct row pairs, each at Hamming distance 2396 |
| Pairing search | `evidence/universal.cpp` | no pairing for four independent variables (54 search nodes); with $x_1=x_2$ the paper's row pairing is found (58 nodes) |
| Source derivation | `evidence/derive.cpp` via `make source` | data SHA-256 `56feb86ad4a71c5e89b6b8ffb1e3e7b7f1271cf37d85e878d9b4a3ac3ddc7dba`; conference matrix of order 46 with $C^2=45I$; $J^2=-I$, $JC=-CJ$; $R$ and $S$ match `wt23.txt` |

`make verify` took about 9 seconds on one core. Tools: Apple clang 21.0.0; pdfTeX 1.40.22 (TeX Live 2021). The paper PDF hash is recorded at the release candidate.

## Independent checks before packaging

Before this repository was assembled, the order-598 certificate was checked by a separately written decoder, and a separately written numpy implementation of Theorem 1 produced the same matrix of order 4792 (up to the polarity of the bit encoding); its full Gram matrix was computed in floating point, where all partial sums are exact integers. The construction was also checked by an AI reviewer working in a separate context on the platform that found it, and again on a second platform by a reviewer who had seen the first review. See [audit/LEDGER.md](audit/LEDGER.md).
