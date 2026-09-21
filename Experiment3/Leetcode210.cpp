#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // Build the adjacency list and compute in-degrees for each course
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        
        for (const auto& pre : prerequisites) {
            int course = pre[0];
            int prerequisite = pre[1];
            adj[prerequisite].push_back(course);
            inDegree[course]++;
        }
        
        // Queue to store courses that have no prerequisites
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> order;
        
        // Process the courses
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            order.push_back(curr);
            
            // "Take" the current course and reduce the in-degree of its neighbors
            for (int nextCourse : adj[curr]) {
                inDegree[nextCourse]--;
                // If a neighbor's in-degree hits 0, all its prerequisites are fulfilled
                if (inDegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        // If we were able to take all courses, return the valid order
        if (order.size() == numCourses) {
            return order;
        }
        
        // If there's a cycle, we won't be able to take all courses
        return {};
    }
};
