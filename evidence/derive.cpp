// Re-derive the order-23 blocks S and R from Maksimovic's published two-graph data.
//
//   derive 46_descendants6.txt phi114-involution.txt wt23.txt
//
// The data file lists descendants (graphs on 45 vertices) of regular two-graphs on 46
// vertices as 45 lines of 45 adjacency digits, one block per descendant. We take block 114,
// discarding whitespace-only lines and whitespace. Bordering its Seidel matrix (-1 for an
// edge, +1 for a non-edge, 0 on the diagonal) with a row and column of ones gives a symmetric
// conference matrix C of order 46, with C^2 = 45 I. The certificate lists a fixed-point-free
// involution p and signs s; the signed permutation J e_i = s_i e_{p(i)} satisfies J^2 = -I
// and J C = -C J. Taking e_f for the smaller vertex f of each pair, followed by J e_f, as a
// basis, C becomes [[R, S], [S, -R]]. The program checks these identities and compares R and
// S with wt23.txt.
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
void require(bool ok, const std::string& what) {
    if (!ok) throw std::runtime_error(what);
}
using Mat = std::vector<std::vector<int>>;
constexpr int V = 46, D = 45, H = 23, BLOCK = 114;

Mat conference_from_data(const char* path) {
    std::ifstream in(path);
    require(bool(in), "cannot open " + std::string(path));
    std::vector<std::string> lines;
    for (std::string line; std::getline(in, line);) {
        std::string compact;
        for (char ch : line)
            if (ch != ' ' && ch != '\t' && ch != '\r') compact += ch;
        if (!compact.empty()) lines.push_back(compact);
    }
    require(lines.size() % D == 0 && lines.size() >= size_t(BLOCK) * D, "unexpected data layout");
    Mat C(V, std::vector<int>(V, 0));
    for (int k = 1; k < V; ++k) C[0][k] = C[k][0] = 1;
    for (int i = 0; i < D; ++i) {
        const std::string& row = lines[size_t(BLOCK - 1) * D + i];
        require(row.size() == size_t(D), "row length");
        for (int j = 0; j < D; ++j) {
            require(row[j] == '0' || row[j] == '1', "adjacency digit");
            if (i == j) require(row[j] == '0', "loop in descendant");
            else C[i + 1][j + 1] = row[j] == '1' ? -1 : 1;
        }
    }
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j) {
            require(C[i][j] == C[j][i], "C must be symmetric");
            int s = 0;
            for (int k = 0; k < V; ++k) s += C[i][k] * C[j][k];
            require(s == (i == j ? D : 0), "C C^T must be 45 I");
        }
    return C;
}

Mat read_wt(const char* path, Mat& R) {
    std::ifstream in(path);
    require(bool(in), "cannot open " + std::string(path));
    std::vector<std::string> rows;
    for (std::string line; std::getline(in, line);)
        if (!line.empty() && line[0] != '#') rows.push_back(line);
    require(rows.size() == 2 * H, "wt23.txt rows");
    Mat S(H, std::vector<int>(H));
    R.assign(H, std::vector<int>(H));
    for (int i = 0; i < 2 * H; ++i)
        for (int j = 0; j < H; ++j) {
            char ch = rows[i].at(j);
            (i < H ? S[i][j] : R[i - H][j]) = ch == '+' ? 1 : ch == '-' ? -1 : 0;
        }
    return S;
}
}  // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 4, "usage: derive 46_descendants6.txt phi114-involution.txt wt23.txt");
        Mat C = conference_from_data(argv[1]);
        std::cout << "two-graph 114: symmetric conference matrix of order 46, C^2 = 45 I\n";
        std::vector<int> p(V, -1), s(V, 0);
        std::ifstream cert(argv[2]);
        require(bool(cert), "cannot open certificate");
        for (std::string line; std::getline(cert, line);) {
            if (line.empty() || line[0] == '#') continue;
            std::istringstream ls(line);
            int i, pi, si;
            require(bool(ls >> i >> pi >> si) && i >= 0 && i < V && pi >= 0 && pi < V && (si == 1 || si == -1),
                    "certificate line");
            p[i] = pi;
            s[i] = si;
        }
        for (int i = 0; i < V; ++i) require(p[i] >= 0 && p[i] != i && p[p[i]] == i, "p must be a fixed-point-free involution");
        // J[p(i)][i] = s_i
        Mat J(V, std::vector<int>(V, 0));
        for (int i = 0; i < V; ++i) J[p[i]][i] = s[i];
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j) {
                int jj = 0, jc = 0, cj = 0;
                for (int k = 0; k < V; ++k) { jj += J[i][k] * J[k][j]; jc += J[i][k] * C[k][j]; cj += C[i][k] * J[k][j]; }
                require(jj == (i == j ? -1 : 0), "J^2 must be -I");
                require(jc == -cj, "J must anticommute with C");
            }
        std::cout << "signed involution: J^2 = -I and J C = -C J\n";
        std::vector<int> first;
        for (int i = 0; i < V; ++i)
            if (i < p[i]) first.push_back(i);
        require(int(first.size()) == H, "23 pairs");
        Mat R0;
        Mat S0 = read_wt(argv[3], R0);
        for (int k = 0; k < H; ++k)
            for (int l = 0; l < H; ++l) {
                int fk = first[k], fl = first[l];
                require(C[fk][fl] == R0[k][l], "R differs from wt23.txt");
                require(s[fl] * C[fk][p[fl]] == S0[k][l], "S differs from wt23.txt");
                // the other two blocks: S and -R
                require(s[fk] * C[p[fk]][fl] == S0[k][l], "lower-left block must equal S");
                require(s[fk] * s[fl] * C[p[fk]][p[fl]] == -R0[k][l], "lower-right block must equal -R");
            }
        std::cout << "C = [[R, S], [S, -R]] in the paired basis; R and S match wt23.txt\n";
    } catch (const std::exception& e) {
        std::cerr << "derive: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
