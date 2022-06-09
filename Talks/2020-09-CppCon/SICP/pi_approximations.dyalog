
⍝ Leibniz
pi ← {+/4÷(⍵⍴1 ¯1)×¯1+2×⍳⍵} ⍝ original
pi ← {+/4÷(×-\⍳⍵)×¯1+2×⍳⍵}  ⍝ sign of alternating sums

⍝ John Wallis
pi ← {4×÷∘⍵*∘2×/(⊣÷-∘1)1↓2×⍳⍵}
pi ← {4÷⍵÷2*⍨×/1(⊢÷-)1↓2×⍳⍵}
pi ← {÷÷/⍵,,⍨⌽⍳2×⍵}
pi ← ÷÷2÷.*⍨∘⍳+⍨
