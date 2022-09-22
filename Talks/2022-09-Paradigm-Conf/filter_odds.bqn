arr ← 1‿2‿3‿4‿5

FilterOdds ← {(2|𝕩)/𝕩}
FilterOdds ← {𝕩/˜2|𝕩}
FilterOdds ← (2|⊢)/⊢
FilterOdds ← ⊢/˜2|⊢

FilterOdds arr # ⟨ 1 3 5 ⟩
