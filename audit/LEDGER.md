# Review ledger

Append-only. Each row records an audit, its scope, the auditor type, findings and dispositions.

| Date | Audit | Auditor | Scope | Result | Disposition |
|---|---|---|---|---|---|
| 2026-11-27 | Literal certificate check (before release packaging) | Claude Code claude-opus-5-5, not cold | $SH(598,SP_2)$ Gram, 357604 tiles, real Gram of order 1196 | VERIFIED | — |
| 2026-11-27 | Explicit build of order 4792 (before release packaging) | Claude Code claude-opus-5-5 | Independent numpy implementation of Theorem 1; full Gram in float32 and float64 | VERIFIED; identical to the release build up to bit polarity | — |
| 2026-11-27 | Priority scan | Claude Code claude-opus-5-5 and a Sonnet subagent | See [PRIOR-ART.md](PRIOR-ART.md) | No earlier construction found | — |
| 2026-11-27 | Proof audit | Process-separated AI reviewer (Claude, frontier model), read-only | Paper Sections 2–6 against the code; independent rebuilds | NO MATH ERROR FOUND; 7 sharpening/documentation findings | All applied; see [reviews/proof-audit.md](reviews/proof-audit.md) |
| 2026-11-27 | Claims and citations audit | Process-separated AI reviewer (Claude Sonnet), read-only | Consistency across surfaces; 16 references; source claims; hygiene | No error in principal claim; 7 findings | All applied; see [reviews/claims-citations-audit.md](reviews/claims-citations-audit.md) |
| 2026-11-27 | Fresh-archive reproduction | Author's session | `git archive 4bd54ed`, `make verify`, `make paper` | All checks passed; PDF byte-identical | — |
