# A Hadamard matrix of order 4792

Jeffery Kline

**Status: release candidate for version 0.1.0.** No DOI exists yet. Admission under Kline's [research standard](https://jeff-kline.github.io/posts/research-program/index.html) is pending; see the [release record](ADMISSION.md). [Read the paper](paper/main.pdf) · [LaTeX source](paper/main.tex)

We construct a Hadamard matrix of order **4792** $=8\cdot599$. This order is listed as open in the 2026 survey by Egan, Kotsireas, London and Ó Catháin, and in the current list of unknown orders. [Survey, Table 5](https://arxiv.org/html/2610.27175v2) · [List of unknown orders](https://www.math74.com/Hadamard/unknown.html)

Miyamoto's 1991 theorem gives a Hadamard matrix of order $8m$ from two ingredients: a conference matrix of order $m+1$, and a quaternary Hadamard matrix of order $m-1$, whose entries are $\pm1$ and $\pm i$. For $m=599$ Paley's construction supplies the conference matrix, but we know of no quaternary Hadamard matrix of order 598. We relax the second ingredient. A real Hadamard matrix of order $2(m-1)$ suffices, provided its rows and columns can be paired so that every two-by-two block is itself a Hadamard matrix. Quaternary inputs are exactly the case in which every block has the same determinant. The relaxation allows determinants of both signs.

## What is new

Miyamoto's theorem and the Paley conference matrix of order 600 were known. The paired-block form of Hadamard matrices goes back to Craigen's signed groups. The new contributions are these.

- **Order 4792 (principal result).** A Hadamard matrix of order 4792, with every entry and its full Gram matrix verified.
- **The relaxed input.** A conference matrix of order $m+1$ and a paired-block Hadamard matrix of order $2(m-1)$ give a Hadamard matrix of order $8m$. This extends Miyamoto's theorem from rotations to rotations and reflections. Our proof is an explicit real construction. Miyamoto's printed argument does not transfer to reflections without a repair, which we record.
- **The paired-block matrix of order 1196.** We substitute Williamson-type matrices of order 23 into the Baumert–Hall array of order 52 that SageMath builds from T-sequences of length 13. No pairing works for every substitution. One pairing works whenever two of the four Williamson-type matrices are equal. More generally, any Williamson-type quadruple of order $w$ with two equal members gives a paired-block Hadamard matrix of order $52w$.
- **Two equal Williamson-type matrices of order 23.** We obtain them from a self-complementary regular two-graph on 46 vertices published by Maksimović. A fixed-point-free involution that complements the two-graph splits its conference matrix into four blocks. These give the quadruple $S,S,I+R,R-I$.

Novelty is bounded to the searched corpus. See the [prior-art record](audit/PRIOR-ART.md).

## Earlier work

Miyamoto's Theorem 7 builds a quaternary Hadamard matrix of order $4m$, and hence a real one of order $8m$, from a conference matrix of order $m+1$ and a quaternary Hadamard matrix of order $m-1$. Our proof follows the eight-block construction of Seberry and Yamada (Lemma 8.12), with its Williamson-type input replaced by the paired-block matrix. Craigen introduced signed-group Hadamard matrices; a paired-block Hadamard matrix of order $2k$ is the expansion of an $SH(k,SP_2)$ in his notation. The array of order 52 is Cooper and Wallis's construction in the Goethals–Seidel layout, with T-sequences that SageMath builds from Turyn sequences of length 7. Symmetric conference matrices of order 46 go back to Mathon (1978). Turyn's infinite family of Williamson matrices also has two equal members; it needs a prime power $q=2w-1$, and $45$ is not one. Full references are in the paper. [Miyamoto 1991](https://doi.org/10.1016/0097-3165(91)90008-5) · [Craigen 1995](https://doi.org/10.1016/0097-3165(95)90002-0) · [Maksimović 2023](https://doi.org/10.3390/sym15020408)

The predecessor release made the same relaxation from rotations to reflections for Kumar's construction of order $4(q+2)$ and gave orders 5164 and 8332. [Orders 5164 and 8332](https://doi.org/10.5281/zenodo.24519197)

## Evidence and limits

| Claim | Status | Evidence |
|---|---|---|
| Theorem 1 (conference matrix and paired-block matrix give order $8m$) | Proved on paper | Section 3 of the paper; explicit construction, checked here at order 4792 |
| Pairing lemma for the order-52 array | Certified computation | All 676 blocks checked symbolically by `evidence/build.cpp` |
| No pairing works for four independent variables | Certified computation | Exhaustive search, `evidence/universal.cpp`; with $x_1=x_2$ the same search finds the paper's pairing |
| Williamson-type matrices of order 23 | Proved on paper and checked | Proposition in Section 5; commutation and Gram checked; re-derived from Maksimović's published data by `make source` |
| $SH(598,SP_2)$ and the paired-block matrix of order 1196 | Certified computation | Full Gram of both, by a separate verifier |
| Hadamard matrix of order 4792 | Certified computation | All 11,479,236 pairs of rows at distance 2396 |
| Order 4792 was open | Literature | Listed in the survey's Table 5 and in the list of unknown orders; search recorded in [PRIOR-ART.md](audit/PRIOR-ART.md) |

The matrix is checked as a whole, so the order-4792 claim does not depend on the general proof of Theorem 1. Equivalence of this matrix to other Hadamard matrices was not studied.

## Rebuild and verify

From this directory, with a C++17 compiler, run

```sh
make verify
```

The script compiles the builder, the verifier and the pairing search. It rebuilds both certificates from `evidence/wt23.txt`, compares them with the shipped files and their pinned SHA-256 digests, checks the shipped files with the separate verifier, and runs the pairing search. It takes about ten seconds. [Builder](evidence/build.cpp) · [Verifier](evidence/verify.cpp) · [Pairing search](evidence/universal.cpp) · [Script](verify.sh)

To re-derive the order-23 matrices from Maksimović's published data, run `make source`. It downloads the data file, checks its pinned SHA-256 digest, and runs [derive.cpp](evidence/derive.cpp) with the [involution certificate](evidence/phi114-involution.txt). The data file is not redistributed here.

**Formats.** `evidence/sh598.sp2` has 598 lines of 598 digits. Digit $d$ is the $2\times2$ signed permutation matrix obtained from the identity by exchanging its columns if bit 2 of $d$ is set, then negating its first row if bit 0 is set and its second row if bit 1 is set. `evidence/H4792.packed.gz` is gzip-compressed; the packed file has 4792 rows of 599 bytes, with bits running from most to least significant and 1 denoting a minus sign.

| File | SHA-256 |
|---|---|
| `evidence/sh598.sp2` | `a7e2e4ce8b817cb281c8cd95268939d64242177e78923714134c66ac508ce217` |
| `H4792.packed` (uncompressed) | `a92ec95ed93df69d68685818dbe191a7021af4bf4bccdd8f179d9c12d32cc59a` |

## Typeset the paper

```sh
make paper
```

## Role of AI

AI assisted the derivations, the computer verification, the literature search and the exposition under the author's direction. Process-separated AI reviews checked the proofs and certificates; they are not independent expert peer review, and no independent human expert has examined the proofs. The [attribution record](audit/ATTRIBUTION.md) and [review ledger](audit/LEDGER.md) record who did what.

[Verification record](VERIFICATION.md) · [Citation](CITATION.cff) · [Correction policy](CORRECTIONS.md) · [License](LICENSE)
