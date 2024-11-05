#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using Pos = pair<ll, ll>;

ll R, C;
vvl bd, air;
vvb visit;

vl dr{-1, 1, 0, 0};
vl dc{0, 0, -1, 1};

void MakeAir(ll r, ll c) {
  queue<Pos> Q{};
  Q.push({r, c});
  visit[r][c] = true;

  while (!Q.empty()) {
    auto [fr, fc] = Q.front();
    Q.pop();

    for (auto d = 0; d < 4; ++d) {
      const auto& nr = fr + dr[d];
      const auto& nc = fc + dc[d];

      if (nr < 0 || R <= nr || nc < 0 || C <= nc) continue;
      if (bd[nr][nc] == 1) continue;
      if (air[nr][nc] == 1) continue;
      if (visit[nr][nc]) continue;

      Q.push({nr, nc});
      air[nr][nc] = 1;
      visit[nr][nc] = true;
    }
  }
}

void Update(ll r, ll c) {
  queue<Pos> Q{};
  Q.push({r, c});
  visit[r][c] = true;

  while (!Q.empty()) {
    auto [fr, fc] = Q.front();
    Q.pop();

    for (auto d = 0; d < 4; ++d) {
      const auto& nr = fr + dr[d];
      const auto& nc = fc + dc[d];

      if (nr < 0 || R <= nr || nc < 0 || C <= nc) continue;
      if (bd[nr][nc] == 1) continue;

      if (air[nr][nc] == 1) {
        bd[fr][fc] = 2;
        break;
      }
    }

    for (auto d = 0; d < 4; ++d) {
      const auto& nr = fr + dr[d];
      const auto& nc = fc + dc[d];

      if (nr < 0 || R <= nr || nc < 0 || C <= nc) continue;
      if (bd[nr][nc] == 0) continue;
      if (visit[nr][nc]) continue;

      Q.push({nr, nc});
      visit[nr][nc] = true;
    }
  }

  for (auto&& row : bd) {
    for (auto&& col : row) {
      if (col == 2) col = 0;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> R >> C;
  bd = vvl(R, vl(C));
  for (auto&& r : bd) {
    for (auto&& c : r) cin >> c;
  }
  air = vvl(R, vl(C, 0));
  for (auto i = 0; i < R; ++i) {
    air[i][0] = 1;
    air[i][C - 1] = 1;
  }
  for (auto j = 0; j < C; ++j) {
    air[0][j] = 1;
    air[R - 1][j] = 1;
  }

  auto bf = bd;
  auto t = 0;
  while (true) {
    ll ch = 0;
    for (const auto& row : bd) {
      for (const auto& col : row) {
        if (col != 0) ++ch;
      }
    }

    if (ch == 0) {
      ll ans = 0;
      for (const auto& row : bf) {
        for (const auto& col : row) {
          if (col != 0) ++ans;
        }
      }

      cout << t << '\n' << ans;
      return 0;
    }

    bf = bd;
    ++t;
    visit = vvb(R, vb(C, false));
    for (auto i = 0; i < R; ++i) {
      for (auto j = 0; j < C; ++j) {
        if (visit[i][j]) continue;
        if (air[i][j] == 0) continue;
        MakeAir(i, j);
      }
    }

    visit = vvb(R, vb(C, false));
    for (auto i = 0; i < R; ++i) {
      for (auto j = 0; j < C; ++j) {
        if (visit[i][j]) continue;
        if (bd[i][j] == 0) continue;

        ++ch;
        Update(i, j);
      }
    }
  }

  return 0;
}