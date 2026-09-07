class Solution {
public:
    vector<int> constructRectangle(int area) {
        for (int w = sqrt(area); w >= 1; w--) {
            if (area % w == 0) {
                return {area / w, w};
            }
        }

        return {};
    }
};
