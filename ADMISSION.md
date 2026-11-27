# Release record

Current verdict: NOT YET ADMITTED.

This paper is prepared for version 0.1.0 under Kline's [research standard](https://jeff-kline.github.io/posts/research-program/index.html). Admission requires a tagged release and verification of the version DOI and the provider archive. Independent expert peer review remains outstanding.

| Gate | Status | Evidence |
|---|---|---|
| P1 · Earlier work and attribution | PARTIAL | Order 4792 is listed as open in the November 2026 survey and in the list of unknown orders. Search log: [PRIOR-ART.md](audit/PRIOR-ART.md). Credit: Miyamoto, Seberry–Yamada, Craigen, Cooper–Wallis, Goethals–Seidel, Turyn, Kharaghani–Tayfeh-Rezaie, SageMath, Mathon, Maksimović, Paley. A rescan is due before tagging. |
| A1 · Claims and verification | PASS | Proof audit: no math error. Claims and citations audit: no error in the principal claim. All findings applied. See the [review ledger](audit/LEDGER.md) and the [verification record](VERIFICATION.md). |
| R1 · Release and reproduction | PARTIAL | `make verify` and `make paper` reproduce from a clean archive. Tag, archive and DOI pending. |

## Residuals

- Maksimović's Table 12 was read by the author from the published PDF on November 27, 2026: two-graphs 114–121 on 46 vertices have automorphism groups of order 6 and are self-complementary. The construction does not depend on the table; `make source` re-derives the order-23 matrices from the published data file and checks every identity used.
- Turyn's 1972 family is described from secondary sources. It is a side remark.
- Equivalence of this matrix to other Hadamard matrices was not studied.
