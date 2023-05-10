⍝ Problem Link: https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/

MinNumber ← {⌊/⍎∘∪¨,⍺(∘.,⍥(⍕¨))⍵}
      
⍝ Tests
  4 1 3 MinNumber 5 7   ⍝ 15
3 5 2 6 MinNumber 3 1 7 ⍝ 3
