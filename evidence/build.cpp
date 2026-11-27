// Build a Hadamard matrix of order 4792 = 8 * 599.
//
//   build wt23.txt sh598.sp2 H4792.packed
//
// Step 1. Read the order-23 blocks S, R and check that S, S, I+R, R-I are symmetric,
//         pairwise commuting sign matrices with S^2 + S^2 + (I+R)^2 + (R-I)^2 = 92 I.
// Step 2. Form the Baumert-Hall array of order 52 that SageMath builds from the
//         T-sequences of length 13 (Goethals-Seidel layout) and check its formal Gram.
// Step 3. Substitute the quadruple, pair rows and columns, and check that every 2x2 block
//         has entry product -1. Write the signed-permutation array SH(598, SP2).
// Step 4. Apply the construction of the paper (Theorem 1) with the Paley conference
//         matrix of order 600 and write the packed Hadamard matrix of order 4792.
//
// Packed format: 4792 rows of 599 bytes; bits run from most to least significant
// within each byte; 1 denotes -1 and 0 denotes +1.
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

[[noreturn]] void fail(const std::string& what) { throw std::runtime_error(what); }
void require(bool ok, const std::string& what) { if (!ok) fail(what); }

constexpr int w = 23;             // Williamson-type order
constexpr int t = 13;             // T-sequence length
constexpr int outer = 4 * t;      // Baumert-Hall order 52
constexpr int half = outer / 2;   // 26 row (column) pairs of the outer array
constexpr int N = half * w;       // 598: order of the signed-permutation array
constexpr int F_order = 2 * N;    // 1196: order of the paired-block Hadamard matrix
constexpr int m = 599;            // Paley prime, m = 2n + 1
constexpr int n = (m - 1) / 2;    // 299
constexpr int order = 8 * m;      // 4792

using Mat = std::vector<std::vector<int>>;
Mat zeros(int r, int c) { return Mat(r, std::vector<int>(c, 0)); }

constexpr int H2[2][2] = {{1, 1}, {1, -1}};

// ---------------------------------------------------------------- step 1
std::array<Mat, 4> read_quadruple(const char* path) {
    std::ifstream in(path);
    require(bool(in), "cannot open " + std::string(path));
    std::vector<std::string> rows;
    for (std::string line; std::getline(in, line);)
        if (!line.empty() && line[0] != '#') rows.push_back(line);
    require(rows.size() == 2 * w, "wt23.txt must have 46 data rows");
    Mat S = zeros(w, w), R = zeros(w, w);
    for (int i = 0; i < 2 * w; ++i) {
        require(rows[i].size() == w, "wt23.txt row length");
        for (int j = 0; j < w; ++j) {
            char ch = rows[i][j];
            int v = ch == '+' ? 1 : ch == '-' ? -1 : ch == '0' ? 0 : 2;
            require(v != 2, "wt23.txt symbol");
            (i < w ? S[i][j] : R[i - w][j]) = v;
        }
    }
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < w; ++j) {
            require(S[i][j] == S[j][i] && R[i][j] == R[j][i], "S and R must be symmetric");
            require(std::abs(S[i][j]) == 1, "S must be a sign matrix");
            require((i == j) == (R[i][j] == 0), "R must have zero diagonal and signs elsewhere");
        }
    std::array<Mat, 4> W{S, S, R, R};
    for (int i = 0; i < w; ++i) { W[2][i][i] = 1; W[3][i][i] = -1; }
    // pairwise commuting (hence amicable, being symmetric) and summed Gram 92 I
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < w; ++j) {
            int gram = 0;
            for (int a = 0; a < 4; ++a)
                for (int k = 0; k < w; ++k) gram += W[a][i][k] * W[a][j][k];
            require(gram == (i == j ? 4 * w : 0), "summed Gram of the quadruple");
            for (int a = 0; a < 4; ++a)
                for (int b = a + 1; b < 4; ++b) {
                    int ab = 0, ba = 0;
                    for (int k = 0; k < w; ++k) { ab += W[a][i][k] * W[b][k][j]; ba += W[b][i][k] * W[a][k][j]; }
                    require(ab == ba, "quadruple members must commute");
                }
        }
    std::cout << "quadruple S, S, I+R, R-I of order 23: symmetric, commuting, summed Gram 92 I\n";
    return W;
}

// ---------------------------------------------------------------- step 2
int modt(int x) { return ((x % t) + t) % t; }

// The order-52 array, as built by SageMath's hadamard_matrix_cooper_wallis_construction:
// T-sequences T1..T4 of length 13 (from the Turyn sequences of length 7), circulants
// X_k[i][j] = T_k[j - i], the Goethals-Seidel array
//   GS(A,B,C,D) = [[A, BR, CR, DR], [-BR, A, -D^T R, C^T R], [-CR, D^T R, A, -B^T R], [-DR, -C^T R, B^T R, A]]
// with R the back-diagonal permutation, and e1 = GS(X1,X2,X3,X4), e2 = GS(X2,-X1,X4,-X3),
// e3 = GS(X3,-X4,-X1,X2), e4 = GS(X4,X3,-X2,-X1). The formal entry is +-v where e_v is the
// unique nonzero e_k at that position.
int array_entry(int r, int c) {
    static int L[outer][outer];
    static bool ready = false;
    if (!ready) {
        const int T[4][t] = {{1, 1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 1, 1, -1, 1, -1, -1},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        // X(k, sign)[i][j], transposed or not, times R on the right when wanted
        auto X = [&](int k, int i, int j, bool transpose, bool times_R) {
            if (times_R) j = t - 1 - j;          // (M R)[i][j] = M[i][t-1-j]
            if (transpose) std::swap(i, j);
            return T[k][modt(j - i)];
        };
        // GS layout: block (bi, bj) -> (which input 0..3, transpose?, times R?, sign)
        struct Slot { int input; bool tr, R; int sign; };
        const Slot gs[4][4] = {
            {{0, false, false, 1}, {1, false, true, 1}, {2, false, true, 1}, {3, false, true, 1}},
            {{1, false, true, -1}, {0, false, false, 1}, {3, true, true, -1}, {2, true, true, 1}},
            {{2, false, true, -1}, {3, true, true, 1}, {0, false, false, 1}, {1, true, true, -1}},
            {{3, false, true, -1}, {2, true, true, -1}, {1, true, true, 1}, {0, false, false, 1}}};
        // inputs of e1..e4 as (T index, sign)
        const int in_idx[4][4] = {{0, 1, 2, 3}, {1, 0, 3, 2}, {2, 3, 0, 1}, {3, 2, 1, 0}};
        const int in_sgn[4][4] = {{1, 1, 1, 1}, {1, -1, 1, -1}, {1, -1, -1, 1}, {1, 1, -1, -1}};
        for (int r0 = 0; r0 < outer; ++r0)
            for (int c0 = 0; c0 < outer; ++c0) {
                int bi = r0 / t, i = r0 % t, bj = c0 / t, j = c0 % t, entry = 0;
                const Slot& sl = gs[bi][bj];
                for (int v = 0; v < 4; ++v) {
                    int k = in_idx[v][sl.input];
                    int val = sl.sign * in_sgn[v][sl.input] * X(k, i, j, sl.tr, sl.R);
                    if (val == 0) continue;
                    require(entry == 0, "T-sequence supports overlap");
                    entry = (v + 1) * val;
                }
                require(entry != 0, "T-sequence supports do not cover");
                L[r0][c0] = entry;
            }
        ready = true;
    }
    return L[r][c];
}

void check_array_gram() {
    // For every row pair, sum over columns of the formal products must be 13*(x1^2+..+x4^2) on the
    // diagonal and 0 off it: coefficient of x_a x_b (a<b) from both orders, and of x_a^2.
    for (int r = 0; r < outer; ++r)
        for (int s = 0; s <= r; ++s) {
            int coef[4][4] = {};
            for (int c = 0; c < outer; ++c) {
                int e = array_entry(r, c), f = array_entry(s, c);
                int a = std::abs(e) - 1, b = std::abs(f) - 1, sign = (e > 0) == (f > 0) ? 1 : -1;
                if (a > b) std::swap(a, b);
                coef[a][b] += sign;
            }
            for (int a = 0; a < 4; ++a)
                for (int b = a; b < 4; ++b)
                    require(coef[a][b] == ((r == s && a == b) ? t : 0), "formal Gram of the order-52 array");
        }
    std::cout << "order-52 array: formal Gram 13 (x1^2 + x2^2 + x3^2 + x4^2) I\n";
}

// ---------------------------------------------------------------- step 3
std::array<std::array<int, 2>, half> pairing(int even_shift, int odd_shift) {
    std::array<std::array<int, 2>, half> p{};
    std::vector<int> seen(outer, 0);
    for (int x = 0; x < t; ++x) {
        p[x] = {x, 2 * t + modt(even_shift - x)};
        p[t + x] = {t + x, 3 * t + modt(odd_shift - x)};
    }
    for (auto& pr : p) { ++seen[pr[0]]; ++seen[pr[1]]; }
    for (int s : seen) require(s == 1, "pairing is not a partition");
    return p;
}

// F: the paired-block Hadamard matrix of order 1196, tiles on consecutive pairs.
// Pairing lemma of the paper: in each of the 676 blocks of the paired array, the product of the
// four signs is -1; either every variable occurs an even number of times, or x1 and x2 each
// occur an odd number of times and x3, x4 an even number.
void check_symbolic_blocks() {
    auto rows = pairing(6, 1), cols = pairing(10, 5);
    int even = 0, odd12 = 0;
    for (auto& rp : rows)
        for (auto& cp : cols) {
            int sign = 1, mask = 0;
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j) {
                    int e = array_entry(rp[i], cp[j]);
                    sign *= e < 0 ? -1 : 1;
                    mask ^= 1 << (std::abs(e) - 1);
                }
            require(sign == -1, "symbolic block with sign product +1");
            require(mask == 0 || mask == 3, "symbolic block with another odd variable set");
            (mask == 0 ? even : odd12)++;
        }
    require(even == 572 && odd12 == 104, "unexpected block counts");
    std::cout << "paired order-52 array: 676 blocks with sign product -1; " << even
              << " with every variable even, " << odd12 << " with x1 and x2 odd\n";
}

Mat build_paired(const std::array<Mat, 4>& W, const char* sp2_path) {
    auto rows = pairing(6, 1), cols = pairing(10, 5);
    Mat F = zeros(F_order, F_order);
    std::vector<std::string> digits(N, std::string(N, '?'));
    long reflections = 0;
    for (int p = 0; p < half; ++p)
        for (int q = 0; q < half; ++q) {
            int coef[2][2];
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j) coef[i][j] = array_entry(rows[p][i], cols[q][j]);
            for (int a = 0; a < w; ++a)
                for (int b = 0; b < w; ++b) {
                    int R0 = p * w + a, C0 = q * w + b;
                    int T[2][2], prod = 1;
                    for (int i = 0; i < 2; ++i)
                        for (int j = 0; j < 2; ++j) {
                            int e = coef[i][j];
                            T[i][j] = (e < 0 ? -1 : 1) * W[std::abs(e) - 1][a][b];
                            prod *= T[i][j];
                            F[2 * R0 + i][2 * C0 + j] = T[i][j];
                        }
                    require(prod == -1, "a 2x2 block is not a Hadamard matrix");
                    // P = T H2 / 2 is a signed permutation; encode it as a digit 0..7
                    int P[2][2];
                    for (int i = 0; i < 2; ++i) {
                        P[i][0] = (T[i][0] + T[i][1]) / 2;
                        P[i][1] = (T[i][0] - T[i][1]) / 2;
                    }
                    int swap = P[0][0] == 0 ? 1 : 0;
                    int top = P[0][swap], bottom = P[1][1 - swap];
                    require(std::abs(top) == 1 && std::abs(bottom) == 1 && P[0][1 - swap] == 0 && P[1][swap] == 0,
                            "block is not a signed permutation");
                    if (P[0][0] * P[1][1] - P[0][1] * P[1][0] < 0) ++reflections;
                    digits[R0][C0] = char('0' + 4 * swap + (top < 0 ? 1 : 0) + (bottom < 0 ? 2 : 0));
                }
        }
    std::ofstream out(sp2_path, std::ios::binary);
    require(bool(out), "cannot write " + std::string(sp2_path));
    for (auto& line : digits) out << line << '\n';
    require(bool(out), "write failed");
    std::cout << "paired-block matrix of order 1196: all " << long(N) * N
              << " blocks have product -1; " << reflections << " blocks are reflections\n";
    return F;
}

// ---------------------------------------------------------------- step 4
bool is_square_mod(int a) {
    for (int x = 1; x < m; ++x)
        if ((x * x) % m == a) return true;
    return false;
}

std::vector<std::vector<signed char>> theorem(const Mat& F) {
    for (int d = 2; d * d <= m; ++d) require(m % d != 0, "m must be prime");
    require(m % 4 == 3, "skew Paley construction needs m = 3 mod 4");
    std::vector<int> chi(m, 0);
    for (int a = 1; a < m; ++a) chi[a] = is_square_mod(a) ? 1 : -1;
    // Core Q of the skew Paley conference matrix C = [[0, 1^T], [-1, Q]], Q[x][y] = chi(y - x).
    auto Q = [&](int x, int y) { return chi[((y - x) % m + m) % m]; };
    // Halves: positions where row 0 of Q is +1, then -1.
    std::vector<int> ord;
    for (int sgn : {1, -1})
        for (int y = 0; y < m; ++y)
            if (y != 0 && Q(0, y) == sgn) ord.push_back(y);
    require(int(ord.size()) == 2 * n, "halves");
    // calQ = Q* (x) H2, U = I2 (x) calQ, D = I_{2n} (x) H2, V = [[D, F], [F', D]], F' = -(D F D / 2)^T.
    const int L = 2 * F_order;  // 2392
    auto Ufun = [&](int i, int j) -> int {
        if (i / F_order != j / F_order) return 0;
        int a = (i % F_order) / 2, h = i % 2, b = (j % F_order) / 2, g = j % 2;
        return a == b ? 0 : Q(ord[a], ord[b]) * H2[h][g];
    };
    Mat DFD = zeros(F_order, F_order);  // (D F D)[i][j], computed tile by tile
    for (int I = 0; I < N; ++I)
        for (int J = 0; J < N; ++J)
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b) {
                    int s = 0;
                    for (int k = 0; k < 2; ++k)
                        for (int l = 0; l < 2; ++l) s += H2[a][k] * F[2 * I + k][2 * J + l] * H2[l][b];
                    require(s % 2 == 0, "D F D must be even");
                    DFD[2 * I + a][2 * J + b] = s;
                }
    auto Vfun = [&](int i, int j) -> int {
        int bi = i / F_order, bj = j / F_order, x = i % F_order, y = j % F_order;
        if (bi == bj) return x / 2 == y / 2 ? H2[x % 2][y % 2] : 0;
        if (bi == 0) return F[x][y];
        return -DFD[y][x] / 2;
    };
    // Strand order: old index (c, s, t, h) -> new index (s, h, c, t).
    std::vector<int> old_of(L);
    for (int c = 0; c < 2; ++c)
        for (int s = 0; s < 2; ++s)
            for (int tt = 0; tt < n; ++tt)
                for (int h = 0; h < 2; ++h) {
                    int old_index = ((c * 2 + s) * n + tt) * 2 + h;
                    int new_index = ((s * 2 + h) * 2 + c) * n + tt;
                    old_of[new_index] = old_index;
                }
    Mat U = zeros(L, L), V = zeros(L, L);
    for (int i = 0; i < L; ++i)
        for (int j = 0; j < L; ++j) {
            U[i][j] = Ufun(old_of[i], old_of[j]);
            V[i][j] = Vfun(old_of[i], old_of[j]);
            require((U[i][j] == 0) != (V[i][j] == 0), "U and V must have complementary supports");
            require(std::abs(U[i][j] + V[i][j]) == 1, "U + V must be a sign matrix");
        }
    // Strand sums of U are constant on every strand block.
    int Ssum[8][8];
    for (int a = 0; a < 8; ++a)
        for (int b = 0; b < 8; ++b)
            for (int r = a * n; r < (a + 1) * n; ++r) {
                int sum = 0;
                for (int c = b * n; c < (b + 1) * n; ++c) sum += U[r][c];
                if (r == a * n) Ssum[a][b] = sum;
                require(sum == Ssum[a][b], "strand sums of U must be constant");
            }
    // Border: R[(u,a),(s,h,c)] = H2[u][h] N[a][2s+c], N = J4 - 2 I4; K = H2 (x) I2 (x) H2;
    // B = R K / 2 and R' = -S K.
    int Rb[8][8], K[8][8], B[8][8], Rp[8][8];
    for (int u = 0; u < 2; ++u)
        for (int a = 0; a < 4; ++a)
            for (int s = 0; s < 2; ++s)
                for (int h = 0; h < 2; ++h)
                    for (int c = 0; c < 2; ++c)
                        Rb[4 * u + a][4 * s + 2 * h + c] = H2[u][h] * (a == 2 * s + c ? -1 : 1);
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            K[i][j] = H2[i >> 2][j >> 2] * ((i >> 1 & 1) == (j >> 1 & 1)) * H2[i & 1][j & 1];
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            int rk = 0, sk = 0;
            for (int k = 0; k < 8; ++k) { rk += Rb[i][k] * K[k][j]; sk += Ssum[i][k] * K[k][j]; }
            require(rk == 2 || rk == -2, "B = R K / 2 must be a sign matrix");
            require(sk == 1 || sk == -1, "R' = -S K must be a sign matrix");
            B[i][j] = rk / 2;
            Rp[i][j] = -sk;
        }
    // H = [[B, R (x) 1^T_{2n}], [R' (x) 1_{2n}, U (x) J2 + V (x) P]], P = [[1,-1],[-1,1]].
    std::vector<std::vector<signed char>> H(order, std::vector<signed char>(order, 0));
    const int strand = 2 * n;  // 598 core columns per strand after the sector coordinate
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) H[i][j] = B[i][j];
        for (int j = 0; j < 8 * strand; ++j) H[i][8 + j] = Rb[i][j / strand];
    }
    for (int x = 0; x < L; ++x)
        for (int sigma = 0; sigma < 2; ++sigma) {
            int row = 8 + 2 * x + sigma;
            for (int j = 0; j < 8; ++j) H[row][j] = Rp[x / n][j];
            for (int y = 0; y < L; ++y)
                for (int tau = 0; tau < 2; ++tau)
                    H[row][8 + 2 * y + tau] = U[x][y] + V[x][y] * (sigma == tau ? 1 : -1);
        }
    for (auto& r : H)
        for (auto v : r) require(v == 1 || v == -1, "H must be a sign matrix");
    std::cout << "order 4792 matrix assembled from the Paley conference matrix of order 600\n";
    return H;
}

void write_packed(const std::vector<std::vector<signed char>>& H, const char* path) {
    std::ofstream out(path, std::ios::binary);
    require(bool(out), "cannot write " + std::string(path));
    std::vector<unsigned char> row((order + 7) / 8);
    for (auto& r : H) {
        std::fill(row.begin(), row.end(), 0);
        for (int j = 0; j < order; ++j)
            if (r[j] < 0) row[j / 8] |= (unsigned char)(0x80 >> (j % 8));
        out.write(reinterpret_cast<const char*>(row.data()), std::streamsize(row.size()));
    }
    require(bool(out), "write failed");
}

}  // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 4, "usage: build wt23.txt sh598.sp2 H4792.packed");
        auto W = read_quadruple(argv[1]);
        check_array_gram();
        check_symbolic_blocks();
        auto F = build_paired(W, argv[2]);
        auto H = theorem(F);
        write_packed(H, argv[3]);
        std::cout << "wrote " << argv[2] << " and " << argv[3] << "\n";
    } catch (const std::exception& e) {
        std::cerr << "build: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
