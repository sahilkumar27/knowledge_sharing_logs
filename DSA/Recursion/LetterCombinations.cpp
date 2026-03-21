void helper(int ind, string &digits, string letter, vector<string> &map, vector<string> &ans)
{
   // base case
   if (ind == digits.length())
   {
      ans.push_back(letter);
      return;
   }

   // recursion
   string temp = map[digits[ind] - '0'];
   for (int i = 0; i < temp.length(); i++)
   {
      helper(ind + 1, digits, letter + temp[i], map, ans);
   }
}
vector<string> letterCombinations(string digits)
{
   vector<string> map = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
   string letter = "";
   vector<string> ans;
   helper(0, digits, letter, map, ans);
   return ans;
}
// Time complexity: O(n*4^n)
// Space complexity: O(n)