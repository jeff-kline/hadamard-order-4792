# Attribution

The paper and release are by Jeffery Kline. This record states which AI systems did which parts of the work, as the paper's Role of AI section promises. Model names are those recorded in the working ledger.

| Part | Done by | Checked by |
|---|---|---|
| Theorem 1 (weakened eight-block construction), first statement and proof | Joint work in the November 26, 2026 unified-construction campaign: Claude Code sketched the construction and Codex carried it out (statement, proof and exact controls) | Cold proof audit, Codex (gpt-6.2-astra), which found and corrected the printed border; re-traced and implemented independently by Claude Code (claude-opus-5-5) |
| Miyamoto's printed proof over $SP_2$: counterexample and repair | Codex (gpt-6.2-sol) | Coordinator replay recorded in the working ledger |
| Search for a paired-block array of order 52; the pairing with $x_1=x_2$; the repeated-member quadruple of order 23 from Maksimović's two-graph $\Phi_{114}$ | Codex (gpt-6.2-astra, with gpt-6.2-sol as executor) | Codex checker (gpt-6.2-astra) in a separate context; Claude Code (claude-opus-5-5) |
| Literal check of $SH(598,SP_2)$; explicit order-4792 build and Gram check; priority scan | Claude Code (claude-opus-5-5), with a Sonnet subagent for web searches | Separate verifier in this release |
| Release code (`build.cpp`, `verify.cpp`, `derive.cpp`, `universal.cpp`), paper and records | Claude Code (claude-opus-5-5) | Audits listed in [LEDGER.md](LEDGER.md) |

The working records are in a private review workspace and are summarized here; they are not part of this release.
