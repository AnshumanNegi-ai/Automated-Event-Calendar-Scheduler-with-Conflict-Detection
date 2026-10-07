// Compares interval-tree overlap check (O(log N)) with a naive linear scan (O(N)).
#include <chrono>
#include <cstdio>
#include <random>
#include <vector>
#include "IntervalTree.h"

int main() {
    std::mt19937 rng(1);
    const int queries = 2000;
    std::printf("%10s %18s %18s %10s\n", "N", "tree (us/query)", "linear (us/query)", "speedup");
    for (int n : {1000, 10000, 100000}) {
        IntervalTree tree;
        std::vector<TimeSlot> v;
        for (int i = 0; i < n; ++i) {            // disjoint events => worst case for linear scan
            TimeSlot s(i * 10, i * 10 + 5);
            tree.insert(s, i);
            v.push_back(s);
        }
        std::vector<TimeSlot> qs;
        for (int i = 0; i < queries; ++i) {
            int st = (rng() % n) * 10 + 6;       // falls in a gap => no overlap
            qs.emplace_back(st, st + 3);
        }
        using clk = std::chrono::steady_clock;
        volatile int sink = 0;

        auto t0 = clk::now();
        for (auto& q : qs) sink = sink + tree.anyOverlap(q);
        auto t1 = clk::now();
        for (auto& q : qs) { bool hit = false; for (auto& s : v) if (s.overlaps(q)) { hit = true; break; } sink = sink + hit; }
        auto t2 = clk::now();

        double tt = std::chrono::duration<double, std::micro>(t1 - t0).count() / queries;
        double tl = std::chrono::duration<double, std::micro>(t2 - t1).count() / queries;
        std::printf("%10d %18.3f %18.3f %9.1fx\n", n, tt, tl, tl / tt);
    }
}
