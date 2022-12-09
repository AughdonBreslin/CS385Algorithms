class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int>> points = {p1, p2, p3, p4};
		
		// add the points into a set
        set<vector<int>> myset;
        for(vector<int> pt : points){
            myset.insert(pt);
        }
        
		// results stores all the squares can construct
        vector<vector<vector<int>>> results;
        
        for(int i = 0; i < points.size(); i++){
            for(int j = i+1; j < points.size(); j++){
				// if two points are the same, skip
                if(points[i][0] == points[j][0] and points[i][1] == points[j][1]){
                    continue;
                }
				
				// create the other pair of diagonal points 
                vector<vector<int>> res = createDiag(points[i], points[j]);
				
				// if the result has decimals, discard
                if(res.size() != 2) continue; 
				
				// if both diagonal points are in the set, we found a square 
                if(myset.find(res[0]) != myset.end() and myset.find(res[1]) != myset.end()){
                    results.push_back({res[0], res[1], points[i], points[j]});
                }
            }
        }
		
		// divide by two because we double counted the same squares formed by different diagonals
        return results.size()/2 > 0;
        
    }
    
    vector<vector<int>> createDiag(vector<int>& a, vector<int>& c){
        double midX = (a[0] + c[0])/2.0;
        double midY = (a[1] + c[1])/2.0;
        
        double bx = midX - (a[1] - midY);
        double by = midY + (a[0] - midX);
        double dx = midX - (c[1] - midY);
        double dy = midY + (c[0] - midX);
        
		// we discard the non-integer points
        double intpart;
        if(modf(bx, &intpart) != 0 or modf(by, &intpart) != 0 or modf(dx, &intpart) != 0 or modf(dy, &intpart) != 0){
            return {{}};
        }
        return {{(int)bx, (int)by}, {(int)dx, (int)dy}};
    }
};