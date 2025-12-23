/**
 * Author: Thieu Nguyen Huy
 * Description: Edmond-Karp algorithm with SPFA to find the shortest path.
 * Usage: Call myflow.resize(n) to initalize the network.
 * Time: O(F \cdot V \cdot E) in worst cases
 * Status: Well-tested
 */
 
struct MCMF {
    struct Edge {
        int u, v;
        ll capacity, cost, flow = 0;
     
        Edge(int _u = 0, int _v = 0, ll _capacity = 0, ll _cost = 0) {
            u = _u, v = _v, capacity = _capacity, cost = _cost, flow = 0;
        }
    };

    const ll FLOW_INF = (ll)2e18;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    int n, m;

    MCMF(int n = 0) { resize(n); }
 
    void resize(int _n) {
        n = _n, m = 0;
        adj.assign(n + 1, vector<int>()), edges.clear();
    }
 
    int add(int u, int v, ll capacity, ll cost) {
        edges.emplace_back(u, v, capacity, cost);
        edges.emplace_back(v, u, 0, -cost);
        adj[u].emplace_back(m++), adj[v].emplace_back(m++);
        return m - 2;
    }

    bool spfa(int source, int sink, vector<ll> &dist, vector<int> &par) {
        dist.assign(n + 1, INF), par.assign(n + 1, -1);
        vector<bool> inQueue(n + 1, false); queue<int> q;
        dist[source] = 0; inQueue[source] = true; q.emplace(source);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inQueue[u] = false;
            for (auto id : adj[u]) {
                int v = edges[id].v;
                if (edges[id].capacity - edges[id].flow <= 0) continue;
                if (minimize(dist[v], dist[u] + edges[id].cost)) {
                    par[v] = id;
                    if (!inQueue[v]) {
                        inQueue[v] = true;
                        q.emplace(v);
                    }
                }
            }
        }
        return dist[sink] != INF;
    }

    pll minCost(int source, int sink) {
        ll flow = 0, cost = 0; vector<ll> dist; vector<int> par;
        while (spfa(source, sink, dist, par)) {
            ll amount = FLOW_INF - flow; int cur = sink;
            while (cur != source) {
                minimize(amount, edges[par[cur]].capacity - edges[par[cur]].flow);
                cur = edges[par[cur]].u;
            }

            flow += amount, cost += amount * dist[sink], cur = sink;
            while (cur != source) {
                edges[par[cur]].flow += amount;
                edges[par[cur] ^ 1].flow -= amount;
                cur = edges[par[cur]].u;
            }
        }

        return make_pair(flow, cost);
    }
} myflow;