// Exhaustive search for pairings of the rows and columns of the order-52 array L that work
// for every substitution: in each block, the sign product is -1 and every variable occurs an
// even number of times.
//
//   universal          search with four independent variables (expected: none exists)
//   universal merge12  identify x1 with x2 (control: the pairing of the paper must be found)
//
// The array is taken from build.cpp (array_entry), so both programs use the same definition.
#define main build_main
#include "build.cpp"
#undef main

#include <cstdint>

namespace {
constexpr int SZ = 52;
using Row = std::uint64_t;

bool merge12 = false;
int var_bit(int e) {
    int v = std::abs(e) - 1;
    if (merge12 && v == 1) v = 0;
    return 1 << v;
}
// compatible[r][s][c] = bitmask of d with (r,s) x (c,d) a good block
Row compatible[SZ][SZ][SZ];
long nodes = 0;

bool block_ok(int r, int s, int c, int d) {
    int e[4] = {array_entry(r, c), array_entry(r, d), array_entry(s, c), array_entry(s, d)};
    int sign = 1, mask = 0;
    for (int x : e) { sign *= x < 0 ? -1 : 1; mask ^= var_bit(x); }
    return sign == -1 && mask == 0;
}

// Does the graph on vertex set `free` with adjacency adj have a perfect matching?
bool matchable(Row free, const Row adj[SZ]) {
    if (!free) return true;
    int best = -1, best_deg = 99;
    for (Row f = free; f; f &= f - 1) {
        int v = __builtin_ctzll(f);
        int deg = __builtin_popcountll(adj[v] & free & ~(Row(1) << v));
        if (deg < best_deg) { best_deg = deg; best = v; }
    }
    if (best_deg == 0) return false;
    Row rest = free & ~(Row(1) << best);
    for (Row cand = adj[best] & rest; cand; cand &= cand - 1) {
        int u = __builtin_ctzll(cand);
        if (matchable(rest & ~(Row(1) << u), adj)) return true;
    }
    return false;
}

const Row ALL = (Row(1) << SZ) - 1;
std::vector<std::pair<int, int>> chosen;
std::vector<std::pair<int, int>> found;

bool search(Row free_rows, const Row col_adj[SZ]) {
    ++nodes;
    if (!free_rows) {
        if (!matchable(ALL, col_adj)) return false;
        found = chosen;
        return true;
    }
    int r = __builtin_ctzll(free_rows);
    Row rest = free_rows & ~(Row(1) << r);
    for (Row cand = rest; cand; cand &= cand - 1) {
        int s = __builtin_ctzll(cand);
        Row adj[SZ];
        bool dead = false;
        for (int c = 0; c < SZ && !dead; ++c) {
            adj[c] = col_adj[c] & compatible[r][s][c];
            if (!(adj[c] & ~(Row(1) << c))) dead = true;
        }
        if (dead || !matchable(ALL, adj)) continue;
        chosen.push_back({r, s});
        if (search(rest & ~(Row(1) << s), adj)) return true;
        chosen.pop_back();
    }
    return false;
}
}  // namespace

int main(int argc, char** argv) {
    merge12 = argc > 1 && std::string(argv[1]) == "merge12";
    for (int r = 0; r < SZ; ++r)
        for (int s = 0; s < SZ; ++s)
            for (int c = 0; c < SZ; ++c) {
                Row m = 0;
                if (r != s)
                    for (int d = 0; d < SZ; ++d)
                        if (d != c && block_ok(r, s, c, d)) m |= Row(1) << d;
                compatible[r][s][c] = m;
            }
    Row start[SZ];
    for (int c = 0; c < SZ; ++c) start[c] = ALL;
    bool ok = search(ALL, start);
    std::cout << (merge12 ? "x1 = x2: " : "independent variables: ")
              << (ok ? "a pairing exists" : "no pairing exists") << " (" << nodes << " search nodes)\n";
    if (ok) {
        std::cout << "row pairs:";
        for (auto& p : found) std::cout << " (" << p.first << "," << p.second << ")";
        std::cout << "\n";
    }
    return 0;
}
