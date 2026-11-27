// Verify the two certificates independently of the builder.
//
//   verify sh598.sp2 H4792.packed
//
// sh598.sp2: 598 lines of 598 digits 0..7 and a line feed. Digit d is the signed 2x2
// permutation matrix obtained from the identity by exchanging its columns if bit 2 is set,
// then negating its first row if bit 0 is set and its second row if bit 1 is set.
// Checks: replacing each digit by its matrix gives a 1196 x 1196 matrix M with M M^T = 598 I
// (an SH(598, SP2)), and M (I (x) H2), with H2 = [[1,1],[1,-1]], is a Hadamard matrix of
// order 1196 whose 2x2 blocks all have entry product -1.
//
// H4792.packed: 4792 rows of 599 bytes, bits from most to least significant, 1 = -1.
// Check: every two distinct rows differ in exactly 2396 positions, so H H^T = 4792 I.
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
void require(bool ok, const std::string& what) {
    if (!ok) throw std::runtime_error(what);
}

std::vector<unsigned char> slurp(const char* path) {
    std::ifstream in(path, std::ios::binary);
    require(bool(in), "cannot open " + std::string(path));
    return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}

// Rows of a +-1 or 0/+-1 matrix as bit masks: support and negative entries.
struct Rows {
    int words;
    std::vector<std::uint64_t> support, negative;
    Rows(int rows, int cols) : words((cols + 63) / 64), support(size_t(rows) * words), negative(size_t(rows) * words) {}
    void set(int r, int c, int v) {
        if (v == 0) return;
        std::uint64_t bit = std::uint64_t(1) << (c % 64);
        support[size_t(r) * words + c / 64] |= bit;
        if (v < 0) negative[size_t(r) * words + c / 64] |= bit;
    }
    long dot(int r, int s) const {
        long d = 0;
        for (int k = 0; k < words; ++k) {
            std::uint64_t both = support[size_t(r) * words + k] & support[size_t(s) * words + k];
            std::uint64_t diff = (negative[size_t(r) * words + k] ^ negative[size_t(s) * words + k]) & both;
            d += __builtin_popcountll(both) - 2 * __builtin_popcountll(diff);
        }
        return d;
    }
};

long check_gram(const Rows& rows, int n, long diagonal, const std::string& name) {
    long pairs = 0;
    for (int r = 0; r < n; ++r)
        for (int s = 0; s <= r; ++s, ++pairs)
            require(rows.dot(r, s) == (r == s ? diagonal : 0), name + ": Gram fails at rows " +
                                                                    std::to_string(r) + ", " + std::to_string(s));
    return pairs;
}

void verify_sp2(const char* path) {
    const int N = 598;
    auto bytes = slurp(path);
    require(bytes.size() == size_t(N) * (N + 1), "sh598.sp2 must have 598 lines of 598 digits");
    int sp[8][2][2];
    for (int d = 0; d < 8; ++d) {
        int P[2][2] = {{1, 0}, {0, 1}};
        if (d & 4) { P[0][0] = 0; P[0][1] = 1; P[1][0] = 1; P[1][1] = 0; }
        for (int j = 0; j < 2; ++j) {
            if (d & 1) P[0][j] = -P[0][j];
            if (d & 2) P[1][j] = -P[1][j];
        }
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) sp[d][i][j] = P[i][j];
    }
    Rows M(2 * N, 2 * N), F(2 * N, 2 * N);
    long blocks = 0;
    for (int r = 0; r < N; ++r) {
        require(bytes[size_t(r) * (N + 1) + N] == '\n', "each line must end with a line feed");
        for (int c = 0; c < N; ++c) {
            unsigned char ch = bytes[size_t(r) * (N + 1) + c];
            require(ch >= '0' && ch <= '7', "digits must be 0..7");
            const auto& P = sp[ch - '0'];
            int T[2][2], prod = 1;
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j) {
                    M.set(2 * r + i, 2 * c + j, P[i][j]);
                    T[i][j] = P[i][0] + (j == 0 ? P[i][1] : -P[i][1]);  // (P H2)[i][j]
                    prod *= T[i][j];
                    F.set(2 * r + i, 2 * c + j, T[i][j]);
                }
            require(prod == -1, "a 2x2 block of the expansion has product other than -1");
            ++blocks;
        }
    }
    long p1 = check_gram(M, 2 * N, N, "SH(598, SP2)");
    long p2 = check_gram(F, 2 * N, 2 * N, "order-1196 expansion");
    std::cout << "sh598.sp2: SH(598, SP2): the 1196 x 1196 block matrix M has M M^T = 598 I (" << p1
              << " row pairs with the diagonal); its expansion by H2 is Hadamard of order 1196 (" << p2
              << " row pairs); " << blocks << " blocks with product -1\n";
}

void verify_packed(const char* path) {
    const int n = 4792, bytes_per_row = 599, words = (bytes_per_row + 7) / 8;
    auto bytes = slurp(path);
    require(bytes.size() == size_t(n) * bytes_per_row, "H4792.packed must have 4792 rows of 599 bytes");
    std::vector<std::uint64_t> rows(size_t(n) * words, 0);
    for (int r = 0; r < n; ++r)
        for (int b = 0; b < bytes_per_row; ++b)
            rows[size_t(r) * words + b / 8] |= std::uint64_t(bytes[size_t(r) * bytes_per_row + b]) << (8 * (b % 8));
    long pairs = 0;
    for (int r = 0; r < n; ++r)
        for (int s = 0; s < r; ++s, ++pairs) {
            int distance = 0;
            for (int k = 0; k < words; ++k)
                distance += __builtin_popcountll(rows[size_t(r) * words + k] ^ rows[size_t(s) * words + k]);
            require(distance == n / 2, "rows " + std::to_string(r) + " and " + std::to_string(s) +
                                           " differ in " + std::to_string(distance) + " positions");
        }
    std::cout << "H4792.packed: " << pairs << " distinct row pairs, each at distance 2396; H H^T = 4792 I\n";
}
}  // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 3, "usage: verify sh598.sp2 H4792.packed");
        verify_sp2(argv[1]);
        verify_packed(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "verify: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
