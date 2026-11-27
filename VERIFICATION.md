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
| $SH(598,SP_2)$ | `evidence/verify.cpp` | the $1196\times1196$ block matrix $M$ has $MM^{\mathsf T}=598I$ (715,806 row pairs, diagonal included); its expansion by $H_2$ is Hadamard of order 1196 |
| Hadamard matrix of order 4792 | `evidence/verify.cpp` | 11,479,236 distinct row pairs, each at Hamming distance 2396 |
| Pairing search | `evidence/universal.cpp` | no pairing for four independent variables (54 search nodes); with $x_1=x_2$ the paper's row pairing is found (58 nodes) |
| Source derivation | `evidence/derive.cpp` via `make source` | data SHA-256 `56feb86ad4a71c5e89b6b8ffb1e3e7b7f1271cf37d85e878d9b4a3ac3ddc7dba`; conference matrix of order 46 with $C^2=45I$; $J^2=-I$, $JC=-CJ$; $R$ and $S$ match `wt23.txt` |

`make verify` took about 9 seconds on one core. Tools: Apple clang 21.0.0; pdfTeX 1.40.22 (TeX Live 2021). The six-page living paper `paper/main.pdf` built by `make paper` has SHA-256 `558dc056191b32d3a1bf7cc8baa4f99eac1cbaaf6e759f3ebfe4fefe2f2c458e`; the tagged paper's hash is recorded under archive verification.

## Independent checks before packaging

Before this repository was assembled, the order-598 certificate was checked by a separately written decoder, and a separately written numpy implementation of Theorem 1 produced the same matrix of order 4792 (up to the polarity of the bit encoding); its full Gram matrix was computed in floating point, where all partial sums are exact integers. The reviews are listed in the [review ledger](audit/LEDGER.md).

## Archive verification

On November 27, 2026, two downloads of the GitHub zipball of tag `v0.1.0` and the file deposited by Zenodo matched byte for byte: 1,259,020 bytes, SHA-256 `8876d2ce44ffdf547e147cb609f7a67e7e186857d26938dab2823b3f4a50d069`. Its MD5 equals Zenodo's recorded checksum, `62655dd692a1b417fac27a67e9420dff`. The extracted archive passes all 25 manifest entries. The version DOI resolves to the record for Jeffery Kline, dated November 27, 2026, license GPL-3.0. [Zenodo record](https://doi.org/10.5281/zenodo.24597897)

A local `git archive` of the same tag reproduced SHA-256 `45678d38676fb6d8d22dcdfcc3afc07e0e0988f4e529506568fe9eb7e2b2559f` on two builds. The tagged paper has SHA-256 `5cd55e811f4b52595dd7ec14d68554fc683fc989a8832c6da00b2fa2abfcb5ba`. The living paper adds the version DOI to its title page.
