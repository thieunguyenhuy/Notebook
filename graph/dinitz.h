struct Dinitz {
    struct Edge {
        int u, v;
        ll capacity, flow = 0;
     
        Edge(int _u = 0, int _v = 0, ll _capacity = 0) {
            u = _u, v = _v, capacity = _capacity, flow = 0;
        }
    };

    const ll FLOW_INF = (ll)2e18;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    int n, m;

    Dinitz(int n = 0) { resize(n); }
 
    void resize(int _n) {
        n = _n, m = 0;
        adj.assign(n + 1, vector<int>()), edges.clear();
    }
 
    int add(int u, int v, ll capacity) {
        edges.emplace_back(u, v, capacity);
        edges.emplace_back(v, u, 0);
        adj[u].emplace_back(m++), adj[v].emplace_back(m++);
        return m - 2;
    }
 
    ll dfs(int u, int sink, ll pushed) {
        if (u == sink || pushed == 0) return pushed;
        for (int &i = ptr[u]; i < (int)adj[u].size(); ++i) {
            int id = adj[u][i]; Edge e = edges[id];
            if (level[u] + 1 != level[e.v] || e.capacity - e.flow <= 0) continue;
            if (ll p = dfs(e.v, sink, min(pushed, e.capacity - e.flow))) {
                edges[id].flow += p, edges[id ^ 1].flow -= p;
                return p;
            }
        }
        return 0;
    }
 
    ll maxFlow(int source, int sink) {
        ll flow = 0;
        do {
            level = ptr = vector<int>(n + 1, 0);
            queue<int> q; q.emplace(source); level[source] = 1;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (auto id : adj[u]) {
                    if (level[edges[id].v] || edges[id].capacity - edges[id].flow <= 0) continue;
                    level[edges[id].v] = level[u] + 1;
                    q.emplace(edges[id].v);
                }
            }
            while (ll pushed = dfs(source, sink, FLOW_INF)) flow += pushed;
        } while (level[sink] != 0);
        return flow;
    }
 
    vii minCut() { // remember to call maxFlow(source, sink) and be careful of duplicates
        vii cut;
        for (auto it : edges)
            if (level[it.u] && !level[it.v]) cut.emplace_back(it.u, it.v);
        return cut;
    }
} myflow;