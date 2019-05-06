#include <cstdio>
#include <vector>
#include <random>
#include <complex>
#include <limits>
#include <chrono>
#include <functional>
#include <boost/heap/fibonacci_heap.hpp>

using namespace std::chrono;
using vec2_t = std::complex<double>;
static constexpr double INF = std::numeric_limits<double>::infinity();

class Disjoint_Sets
{
    std::vector<int> parent_, rank_;
public:
    Disjoint_Sets(unsigned size)
    {
        parent_.reserve(size); rank_.reserve(size);
        for (unsigned i=0; i<size; ++i) { parent_.push_back(i); rank_.push_back(0); }
    }
    int find(int x)
    {
        if (parent_[x] != x) parent_[x] = find(parent_[x]);
        return parent_[x];
    }
    void union_set(int x, int y)
    {
        int x_root = find(x), y_root = find(y);
        if (x_root == y_root) return;
        else if (rank_[x_root] < rank_[y_root]) parent_[x_root] = parent_[y_root];
        else if (rank_[x_root] > rank_[y_root]) parent_[y_root] = parent_[x_root];
        else
        {
            parent_[y_root] = parent_[x_root];
            rank_[x_root]++;
        }
    }
};

class Graph
{
    std::vector<vec2_t> pos_; std::vector<double> graph_;
public:
    const std::size_t size;
    /*
     * Constructs a randomly connected graph
     * Node positions are distributed/simulated within [0, size)
     * Weight between 2 pts are denoted by their L2 distance
     */
    Graph(std::size_t size) : size(size)
    {
        pos_.reserve(size); graph_.assign(size*size, 0);

        std::uniform_int_distribution<int> rnd(0, size - 1);
        std::mt19937 mersenne(std::random_device{}());
        Disjoint_Sets set(size);

        for (std::size_t i=0; i<size; ++i)
            pos_.push_back({ static_cast<double>(rnd(mersenne)),
                             static_cast<double>(rnd(mersenne)) });
        while (!is_connected(set))
        {
            int i = rnd(mersenne), j = rnd(mersenne);
            if (i == j) continue;
            set.union_set(i, j);
            graph_[get_ix(i, j)] = abs(pos_[i] - pos_[j]);
            graph_[get_ix(j, i)] = graph_[get_ix(i, j)];
        }
    #if 0
        debug_graph();
    #endif
    }

    inline double get_weight(int i, int j) const { return graph_[get_ix(i, j)]; }

    auto get_adjs(unsigned src) const
    {
        std::vector<int> ret;
        for (std::size_t i=0; i<size; ++i)
            if (graph_[get_ix(src, i)] && i != src) ret.push_back(i);
        return ret;
    }

private:
    inline int get_ix(int i, int j) const { return i*size + j; }

    inline bool is_connected(Disjoint_Sets& set)
    {
        for (std::size_t i=0; i<size; ++i)
        for (std::size_t j=i; j<size; ++j)
            if (set.find(i) != set.find(j)) return false;
        return true;
    }

    inline void debug_graph() const
    {
        for (std::size_t i=0; i<size; ++i)
        {
            for (std::size_t j=0; j<size; ++j)
                std::printf("%f\t", graph_[get_ix(i, j)]);
            std::printf("\n");
        }
    }
};

/*
 * Finds all shortest paths from a specified source node
 */
class Dijkstra
{
    const int src_vert_, size_;
    std::vector<double> dist_;
    std::vector<int> prev_;
public:
    Dijkstra(const Graph& g, unsigned src) : src_vert_(src), size_(g.size)
    {
        using nwp = std::pair<int, double>;
        auto compare = [&](const nwp& l, const nwp& r)
            { return l.second > r.second; };

        boost::heap::fibonacci_heap
            <nwp, boost::heap::compare<decltype(compare)>> fh(compare);

        std::vector<decltype(fh)::handle_type> handles(size_);
        dist_.assign(size_, INF); dist_[src_vert_] = 0;
        prev_.assign(size_,  -1);

        for (int i=0; i<size_; ++i)
            handles[i] = (i == src_vert_)
                            ? fh.push({i,   0})
                            : fh.push({i, INF});
        while (!fh.empty())
        {
            auto src = fh.top().first; fh.pop();

            for (const auto& adj: g.get_adjs(src))
            {
                double tmp = dist_[src] + g.get_weight(src, adj);
                if (tmp > dist_[adj]) continue;
                prev_[adj] = src;
                dist_[adj] = tmp;
                fh.decrease(handles[adj], {adj, tmp});
            }
        }
    }
    void trace_paths()
    {
        // Inefficient but ehh
        std::function<void(int)> trace = [&](int goal)
        {
            if (prev_[goal] == -1)
                { std::printf("%d", src_vert_); return; }
            trace(prev_[goal]);
            std::printf(" -> %d", goal);
        };
        for (int i=0; i<size_; ++i)
            { std::printf("Path to %d: ", i); trace(i); std::printf("\n"); }
    }
};

int main()
{
    constexpr unsigned GRAPH_SIZE = 1e4;

    std::printf("Generating graph...\n");
    Graph g(GRAPH_SIZE);

    std::printf("Running Dijkstra's...\n");
    auto stime = high_resolution_clock::now();
    Dijkstra dijk(g, 0);
    auto etime = high_resolution_clock::now();
    dijk.trace_paths();

    duration<double, std::milli> rtime = etime - stime;
    std::printf("Runtime: %f ms\n", rtime.count());
}