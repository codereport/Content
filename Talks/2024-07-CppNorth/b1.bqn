_B1_ ← {𝔽𝕨𝔾𝕩} # ∘ & 2 Train
Zip  ← ⋈¨
Sort ← ∧
Snd  ← ⊑⌽

SortString ← Snd¨ Sort _B1_ Zip

# Test
⟨3,2,1,4⟩ SortString "REPL" # PERL