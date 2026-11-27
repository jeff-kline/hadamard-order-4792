# Proof audit (November 27, 2026)

Auditor: process-separated AI reviewer (Claude, frontier model), read-only, at commit `4bd54ed`. Transcribed from the returned report; scratch scripts were not added to this release.

**Verdict: NO MATH ERROR FOUND.**

What was run:
- `verify.sh`, to scratch: all checks passed.
- An independent numpy rebuild from the text of Section 3 alone. It checked equations (1)–(3), the half-row sums, the strand sums, the border and the Gram. Small cases m = 3 and 7 (skew) and m = 5 and 13 (symmetric) passed. At m = 599, using the decoded `sh598.sp2`, the rebuild was entry-for-entry equal to the shipped matrix of order 4792.
- An independent rebuild of the order-52 array from the displayed T-sequences and the GS array. The support, the orthogonal-design identities and the 572/104 block counts all matched.
- An independent exhaustive pairing search, which reproduced both results.
- `derive.cpp` on freshly downloaded data, digest matching the pin.
- A comparison of the SageMath develop source with the displayed formulas.

Findings and dispositions:

| # | Label | Finding | Disposition |
|---|---|---|---|
| 1 | sharpening | The remark "Corollary needs the repeated member" overstates the search, which shows only that no pairing of $L$ works formally for independent variables. | Fixed: now "no pairing of $L$ works for all Williamson-type quadruples". |
| 2 | sharpening | "All blocks have the same determinant" holds up to the order within pairs. For the order-1196 matrix the determinant pattern is not of the form $r_ic_j$. | Added to Section 2 and to the remark in Section 4 (fact re-checked by the author's script: 162,816 violating positions). The abstract's wording is kept, since it describes the case and Section 2 states it precisely. |
| 3 | sharpening | The symmetric-or-skew hypothesis is removable by Delsarte–Goethals–Seidel. | Fixed: one sentence after Theorem 2 cites [DGS71, Corollary 2.2]. Bibliographic data checked through Crossref; the corollary was confirmed through secondary sources. |
| 4 | documentation | T-sequences are defined with nonperiodic autocorrelation. The displayed GS array uses SageMath's signs. | Fixed both. |
| 5 | documentation | Implicit conventions in Section 3: order of halves, order within halves, how pairs of $F$ correspond to elements, border row order. | Fixed: one sentence states all four. |
| 6 | documentation | Notation collisions: $P$; $R$, $S$, $J$ reused; $S_\pm$ against $S$, $S_Q$. | Fixed: Section 3 uses $\Pi$, $Z$, $Z'$, $\Sigma$, $\Sigma_Q$; Section 5 uses $G$ for the signed involution. |
| 7 | documentation | "A regular two-graph gives a conference matrix" needs "nontrivial". | Fixed. |
| 8 | not verified | Miyamoto's Theorem 7 and (6.1), Seberry–Yamada Lemma 8.12, the open-order status, and "automorphism group of order six" were not checked from primary sources. | Seberry–Yamada and the open-order status were confirmed by the claims audit. Miyamoto was read from the primary source in the review workspace before release. Maksimović's Table 12 was read by the author from the published PDF on November 27, 2026, and confirms two-graphs 114–121 as self-complementary with automorphism group of order 6. |
