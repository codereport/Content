    # Discoring APL (equivalent in BQN)
    ↕5
⟨ 0 1 2 3 4 ⟩
    +´↕5
10
    +`↕5
⟨ 0 1 3 6 10 ⟩

    # C++ Algorithms
    _AnyOf   ← { ∨´𝔽𝕩}
    _AllOf   ← { ∧´𝔽𝕩}
    _NoneOf  ← {¬∨´𝔽𝕩}
    _CountIf ← { +´𝔽𝕩}
    Count    ← { +´𝕨=𝕩}

    # FilterOutHTMLTags
    FilterOutHTMLTags ← {𝕩/˜¬(⊢∨≠`)𝕩∊"<>"}
    FilterOutHTMLTags "<div>Hello <b>CppNorth!</b></div>" 
"Hello CppNorth!"

    # CountLRUD
    CountLRUD ← {+´˘"LRUD"=⌜𝕩}
    CountLRUD "LRDLURDLURDULR" 
⟨ 4 4 3 3 ⟩
