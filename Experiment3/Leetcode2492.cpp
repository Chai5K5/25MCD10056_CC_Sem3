#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Build the adjacency list: adj[u] = {v, distance}
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& road : roads) {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }
        
        int min_score = 1e9;
        vector<bool> visited(n + 1, false);
        queue<int> q;
        
        // Start traversal from city 1
        q.push(1);
        visited[1] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            // Check all connected roads from the current city
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                // Update the minimum score for any road seen in this component
                min_score = min(min_score, weight);
                
                // If the neighboring city hasn't been visited, add it to the queue
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        
        return min_score;
    }
};
