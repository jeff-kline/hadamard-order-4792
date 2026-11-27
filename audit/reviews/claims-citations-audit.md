# Claims and citations audit (November 27, 2026)

Auditor: process-separated AI reviewer (Claude Sonnet), read-only, at commit `4bd54ed`. Transcribed from the returned report.

**Verdict: no error in the principal claim or its numbers.** All numbers agree across README, paper, CITATION.cff, VERIFICATION.md and the output of `verify.sh` (rerun). All 16 bibliography entries match Crossref or publisher data.

Source claims confirmed:
- Table 5 of arXiv:2610.27175v2 lists p = 599 in its 8p row.
- The SageMath T-sequence route and the Cooper–Wallis and GS formulas match the paper verbatim.
- Seberry–Yamada Lemma 8.12 is an eight-block construction, checked against the book PDF.
- The math74 list of unknown orders contains 4792.

Not checked by the auditor:
- Maksimović's Table 12: the publisher returned 403.
- Turyn 1972, two equal members: confirmed through secondary sources only.
- Miyamoto's (6.1).
- The "version 61" label: it is on the main math74 page, not on the list page itself.

| # | Label | Finding | Disposition |
|---|---|---|---|
| 1 | gap | Summaries say "a conference matrix" while Theorem 1 says symmetric or skew. | Resolved without changing approved prose: the paper now cites [DGS71, Corollary 2.2], so the summaries are exact. |
| 2 | gap | The paper's "What is new" lacked the bounded-search qualifier. | Fixed. |
| 3 | documentation | VERIFICATION.md contained reader-facing process history. | Fixed: replaced by a pointer to the ledger. |
| 4 | documentation | Placeholder in ATTRIBUTION.md. | Fixed: the owner confirmed joint authorship. |
| 5 | documentation | "715,806 row pairs" was mislabelled. | Fixed in `verify.cpp` output and VERIFICATION.md: the pairs are rows of the 1196 × 1196 block matrix, diagonal included. |
| 6 | documentation | No PDF hash; title says "Draft". | Fixed at the candidate: title line now reads release candidate; hash in VERIFICATION.md. |
| 7 | documentation | Grammar in Section 4. | Fixed. |
| — | citation | "Version 61" attributed to the list page. | Fixed: the bibliography now says the list accompanies version 61 of the main page. |
