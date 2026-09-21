#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int MOD = 1e9 + 7;
        
        // Build the adjacency list: adj[u] = {v, time}
        vector<vector<pair<int, long long>>> adj(n);
        for (const auto& road : roads) {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }
        
        // dist[i] will store the shortest time to reach node i from 0
        vector<long long> dist(n, 1e18);
        
        // ways[i] will store the number of ways to reach node i in dist[i] time
        vector<long long> ways(n, 0);
        
        // Min-heap to process nodes based on minimum time: {time, node}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        
        dist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});
        
        while (!pq.empty()) {
            auto [currentTime, u] = pq.top();
            pq.pop();
            
            // If we find a longer path in the queue, skip it
            if (currentTime > dist[u]) continue;
            
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                long long travelTime = edge.second;
                
                // If a strictly shorter path is found
                if (dist[u] + travelTime < dist[v]) {
                    dist[v] = dist[u] + travelTime;
                    ways[v] = ways[u];
                    pq.push({dist[v], v});
                } 
                // If another shortest path of the same length is found
                else if (dist[u] + travelTime == dist[v]) {
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }
        return ways[n - 1];
    }
};
