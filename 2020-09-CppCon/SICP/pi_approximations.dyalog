
pi ← {+/4∘÷(⍵⍴1 ¯1)×¯1+2×⍳⍵} ⍝ original
pi ← {+/4∘÷(×-\⍳⍵)×¯1+2×⍳⍵}  ⍝ sign of alternating sums
