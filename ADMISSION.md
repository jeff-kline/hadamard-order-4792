# Release record

Current verdict: ADMITTED

On November 27, 2026, Jeffery Kline admitted version 0.1.0 of *A Hadamard matrix of order 4792* under his [research standard](https://jeff-kline.github.io/posts/research-program/index.html). Admission is a release decision, not peer review or a correctness certificate. Independent expert peer review remains outstanding.

| Gate | Result | Evidence |
|---|---|---|
| P1 · Earlier work and attribution | PASS | Order 4792 is listed as open in the November 2026 survey and in the list of unknown orders. Searches and a rescan before public visibility found no earlier construction. Credit: Miyamoto, Seberry–Yamada, Craigen, Cooper–Wallis, Goethals–Seidel, Turyn, Kharaghani–Tayfeh-Rezaie, SageMath, Delsarte–Goethals–Seidel, Mathon, Maksimović, Paley. [Prior-art record](audit/PRIOR-ART.md) · [Rescan](audit/reviews/p1-rescan-2026-11-27.md) |
| A1 · Claims and verification | PASS | Proof audit: no math error. Claims and citations audit: no error in the principal claim. All findings applied. All 11,479,236 pairs of rows of the matrix are at distance 2396. [Review ledger](audit/LEDGER.md) · [Verification record](VERIFICATION.md) |
| R1 · Release and reproduction | PASS | Tag `v0.1.0` (annotated, object `77f6a11a9da03e27df14362469991b35c24d9252`) fixes commit `551124f3d6440883d5b5ed00edb00799a91ecc77`. The Zenodo file matches the GitHub tag zipball byte for byte. [Tag](https://github.com/jeff-kline/hadamard-order-4792/tree/v0.1.0) · [Version DOI](https://doi.org/10.5281/zenodo.24597897) · [Archive verification](VERIFICATION.md#archive-verification) |

The [public work listing](https://jeff-kline.github.io/#project-hadamard-order-4792) identifies the paper, links the repository and cites the version DOI.

The immutable tag retains its release-candidate status text, because the DOI did not exist when it was made. [All versions](https://doi.org/10.5281/zenodo.24597896)

## Residuals

- Turyn's 1972 family is described from secondary sources. It is a side remark.
- Equivalence of this matrix to other Hadamard matrices was not studied.
