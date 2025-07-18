#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

const int MOD = 1e9 + 7; // మాడ్యులో విలువ

// గ్రాఫ్ కోసం అడ్జసెన్సీ లిస్టులు
std::vector<std::vector<int>> adj;
// రివర్స్ గ్రాఫ్ కోసం అడ్జసెన్సీ లిస్టులు (N నుండి రీచబిలిటీ కోసం)
std::vector<std::vector<int>> rev_adj;

// DP అరే: dp[u] అనేది u నుండి Nకి ఉన్న మార్గాల సంఖ్య
std::vector<int> dp;
// DFS విజిటింగ్ స్టేటస్:
// 0: సందర్శించబడలేదు (unvisited)
// 1: ప్రాసెస్ అవుతోంది (currently in recursion stack - potential cycle)
// 2: ప్రాసెస్ పూర్తయింది (processed)
std::vector<int> visited_state;

// సైకిల్ ద్వారా అనంత మార్గాలను సూచిస్తుంది
bool infinite_paths_found = false;

// N నుండి చేరుకోగల నోడ్‌లను గుర్తించడానికి
std::vector<bool> can_reach_N;

// N నుండి (రివర్స్ గ్రాఫ్‌లో) చేరుకోగల నోడ్‌లను గుర్తించడానికి DFS
void find_can_reach_N(int u) {
    can_reach_N[u] = true;
    for (int v : rev_adj[u]) {
        if (!can_reach_N[v]) {
            find_can_reach_N(v);
        }
    }
}

// ప్రధాన DFS ఫంక్షన్ DP మరియు సైకిల్ డిటెక్షన్ కోసం
void dfs(int u, int N) {
    if (infinite_paths_found) return; // ఇప్పటికే అనంత మార్గాలు కనుగొనబడితే, బయటపడండి

    visited_state[u] = 1; // ప్రాసెస్ అవుతోంది అని గుర్తించండి

    // N నుండి చేరుకోలేని నోడ్‌లను విస్మరించండి (ఆప్టిమైజేషన్)
    if (!can_reach_N[u]) {
        visited_state[u] = 2;
        dp[u] = 0;
        return;
    }

    if (u == N) {
        dp[u] = 1; // N నుండి Nకి ఒకే మార్గం
        visited_state[u] = 2;
        return;
    }

    for (int v : adj[u]) {
        if (infinite_paths_found) return; // అనంత మార్గాలు కనుగొనబడితే, బయటపడండి

        if (visited_state[v] == 1) {
            // సైకిల్ కనుగొనబడింది!
            // ఈ సైకిల్ నుండి Nకి చేరుకోగలమా అని తనిఖీ చేయండి
            if (can_reach_N[v]) {
                infinite_paths_found = true; // అనంత మార్గాలున్నాయి
                return;
            }
            // సైకిల్ ఉంది కానీ Nకి దారి లేదు, కాబట్టి ఈ అంచును విస్మరించండి
            continue;
        }

        if (visited_state[v] == 0) {
            // సందర్శించబడకపోతే, రికర్సివ్‌గా కాల్ చేయండి
            dfs(v, N);
        }

        // DP విలువను అప్‌డేట్ చేయండి
        // v నుండి Nకి మార్గాలు ఉంటే మరియు అనంత మార్గాలు కనుగొనబడకపోతే
        if (dp[v] != -1) { // -1 అంటే ఇంకా లెక్కించబడలేదు లేదా అనంతం అని కాదు
            dp[u] = (dp[u] + dp[v]) % MOD;
        }
    }

    visited_state[u] = 2; // ప్రాసెస్ పూర్తయింది అని గుర్తించండి
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); // వేగవంతమైన I/O కోసం

    int n, m;
    std::cin >> n >> m; // n: నగరాల సంఖ్య, m: మార్గాల సంఖ్య

    adj.resize(n + 1);
    rev_adj.resize(n + 1);
    dp.assign(n + 1, 0); // DP విలువలు 0తో ప్రారంభించండి
    visited_state.assign(n + 1, 0);
    can_reach_N.assign(n + 1, false);

    // గ్రాఫ్ మరియు రివర్స్ గ్రాఫ్‌ను నిర్మించండి
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    // N నుండి ఏ నోడ్‌లను చేరుకోగలమో మొదట గుర్తించండి (రివర్స్ గ్రాఫ్‌లో)
    find_can_reach_N(n);

    // 1 నుండి DFSని ప్రారంభించండి
    // అనంత మార్గాలు కనుగొనబడకపోతే మాత్రమే
    if (can_reach_N[1]) { // 1 నుండి Nకి మార్గం ఉండాలి
        dfs(1, n);
    }

    // ఫలితాన్ని ప్రింట్ చేయండి
    if (infinite_paths_found) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << dp[1] << std::endl;
    }

    return 0;
}

