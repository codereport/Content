arr ← 1 2 3 4 5

filterOdds ← {(2|⍵)/⍵}
filterOdds ← {⍵/⍨2|⍵}
filterOdds ← (2|⊢)⊢⍤/⊢

filterOdds arr ⍝ 1 3 5
