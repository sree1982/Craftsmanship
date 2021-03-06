/*
Binary Tree Maximum Path SumNov 8 '12
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.

*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
       
       int maxFromDownTree = INT_MIN;
       int maxSum = INT_MIN;
       
       maxSumFinder(root, maxFromDownTree, maxSum);
       
        return maxSum;
    }
    
    
    void maxSumFinder(TreeNode *root, int &maxFromDownTree, int &maxSum)
    {
         
        if(root == NULL)
        {
            return;
        }
           
        int lsum = 0; 
        int rsum = 0;
        maxSumFinder(root->left, lsum,maxSum);
        maxSumFinder(root->right, rsum,maxSum);
            
        maxFromDownTree = max(root->val, max(root->val + lsum, root->val + rsum));
        maxSum = max(maxSum, max(maxFromDownTree, root->val + lsum + rsum));
       
    }
};







//Above is better

#include <iostream>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
private:
    int getMaxValue(int num1, int num2)
    {
        if(num1 >= num2)
        {
            return num1;
        }
        else
        {
            return num2;
        }
    }
public:
    int maxPathSum(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int maxSum = INT_MIN;
        int maxOfThreeNode = INT_MIN;
        maxSumOfNode(root, maxOfThreeNode, maxSum);
        return maxSum;
    }
    
    void maxSumOfNode(TreeNode *root, int& maxOfThreeNode, int& maxSum)
    {
        int leftMax = 0;
        int rightMax = 0;
       
        if(root == NULL)
        {
            maxOfThreeNode = 0;
            return;
        }
        maxSumOfNode(root->left, leftMax, maxSum);
        maxSumOfNode(root->right, rightMax, maxSum);
        maxOfThreeNode = getMaxValue(root->val, getMaxValue(root->val + leftMax, root->val + rightMax));
        maxSum = getMaxValue(maxSum,getMaxValue(maxOfThreeNode, root->val + leftMax + rightMax));
        return;        
    }
};