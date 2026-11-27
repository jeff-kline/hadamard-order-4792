# Prior-art record

**Scope.** Has a Hadamard matrix of order 4792 been constructed before? Secondary: is $SH(598,SP_2)$, a quaternary Hadamard matrix of order 598, or a paired-block Hadamard matrix of order 1196 recorded? Novelty below is bounded to this searched corpus.

## Searches on November 27, 2026

| Source | Query or page | Result |
|---|---|---|
| List of unknown orders, version 61 (November 2026) | https://www.math74.com/Hadamard/unknown.html | 81 orders up to 10000 without a construction; 4792 is listed. Smallest open order 2396. |
| Egan, Kotsireas, London, Ó Catháin, arXiv:2610.27175v2 (November 3, 2026) | Table 5, read from the HTML version | Table of orders up to 10000 with no known Hadamard matrix. The row $8p$ lists $p=599, 719, 739, 839, 1031, 1087$, so 4792 is open there. The text credits recent closures (Kumar's $4st$ orders; Miyamoto-type orders 6108, 7532, 9708); 4792 is not among them. |
| GitHub, `gh search repos` | `hadamard 4792`, `hadamard order 4792`, `hadamard 1196 signed`, `signed group hadamard`, `hadamard open orders`, `hadamard new orders`, `miyamoto hadamard`, `williamson two-graph` | No relevant repository. The nearest, bbeartheancient/hoa64 (810 orders up to 7408), has no matrix of order 4792; its Miyamoto module needs $H(q-1)$ with $q$ a prime power, and $4792/4=1198$ is not one. |
| GitHub, `gh search code` | `4792 hadamard`; `4792` and `1198` within hoa64 | No relevant hit. |
| Zenodo REST API | `hadamard AND 4792`; 25 most recent records with "Hadamard" in the title | 0 records; none of the recent records concerns new orders, signed groups, 598 or 1196. |
| Web search (arXiv, Scholar, general) | "Hadamard matrix of order 4792", "4792" Hadamard 1198, "BH(598", "SH(598", signed group $SP_2$, Miyamoto $8q$ | Nothing relevant. |

## Closest mechanisms

| Work | What it gives | Relation |
|---|---|---|
| Miyamoto 1991, Theorem 7 | Conference matrix of order $m+1$ and quaternary Hadamard matrix of order $m-1$ give order $8m$ | Theorem 1 admits reflections in the input. The printed proof uses entrywise conjugation and does not carry over verbatim; a repaired block matrix works (paper, Section 3). |
| Miyamoto 1991, ring remark (p. 97) | The engine of the construction over rings with an anti-involution | With Craigen's expansion this is the natural route to Theorem 1; the repair above is needed. |
| Craigen 1995 | Signed groups, $SH(n,S)$, expansion to real Hadamard matrices (Theorem 5) | Gives the language and the expansion; contains no conference-matrix construction. |
| Seberry and Yamada 1992, Lemma 8.12 and Corollary 8.14 | Eight-block construction of order $8(2n+1)$ with Williamson-type inputs | The proof of Theorem 1 follows its structure, with the input replaced. |
| Kline 2026 (orders 5164 and 8332) | The same rotation-to-reflection relaxation for Kumar's construction of order $4(q+2)$ | Predecessor; different consumer theorem. |
| Turyn 1972 | Williamson matrices of order $(q+1)/2$ with two equal members, $q$ a prime power | Same shape; at order 23 it would need $q=45$. |

## Residuals

- Preprints posted after November 3, 2026, and repositories not indexed by GitHub search, may be missed.
- The searches used general web tools rather than the native arXiv and Scholar interfaces.
- A pre-tag rescan is required within seven days before tagging.
