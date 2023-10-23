/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        //turn tree into an undirected graph by keeping parent pointers
        unordered_map<TreeNode*,TreeNode*> mp;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int sz=q.size();
            for(int i=0;i<sz;++i){
                TreeNode* node=q.front();
                q.pop();
                if(node->left!=NULL){
                    mp[node->left]=node;
                    q.push(node->left);
                }
                if(node->right!=NULL){
                    mp[node->right]=node;
                    q.push(node->right);
                }
            }
        }
        
        //do bfs traversal to find all nodes at distance k from target
        int dist=0;
        vector<int> ans;
        q.push(target);
        unordered_set<TreeNode*> st;
        st.insert(target);
        while(!q.empty()){
            int sz=q.size();
            for(int i=0;i<sz;++i){
                TreeNode* node=q.front();
                q.pop();
                if(k==dist){
                    ans.push_back(node->val);
                }
                if(node->left!=NULL && !st.contains(node->left)){
                    st.insert(node->left);
                    q.push(node->left);
                }
                if(node->right!=NULL && !st.contains(node->right)){
                    st.insert(node->right);
                    q.push(node->right);
                }
                if(mp.contains(node) && !st.contains(mp[node])){
                    st.insert(mp[node]);
                    q.push(mp[node]);
                }
            }
            dist++;
            if(dist==k+1) break;
        }
        return ans;
    }
};
