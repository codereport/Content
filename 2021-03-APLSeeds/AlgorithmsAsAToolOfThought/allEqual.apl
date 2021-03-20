⍝ https://dzaima.github.io/paste#041IAg8ScHNfC0sQchUdtExQedSzXr9Z41NX8qHerpi2QqOUipOpR73Zc6qoNbR91LnrUsQqXAluQMT1d@iBzdB71dOjjNAlkpZEtRB6Xk0Ausn3UtUgTnwKQc3Eo0QA7VxPoXmyyho86ZjzqXApUATRm8aOeHbiMsdUH@wnsH5xOAfmlaxFWV2jA/QHEj3qX6IOZnQtxOlsDFMgwpc0wpQA#APL

allEqual ← ∧/{(⊃⍵)=⍵}
allEqual ← ∧/{(⊃⍵)⍷⍵}
allEqual ← {1=≢∪⍵}
allEqual ← =/{(⌊/⍵),⌈/⍵}
allEqual ← {∧/2=/⍵}

allEqual ← ∧/(⊃=⊢)
allEqual ← ∧/(⊃⍷⊢)
allEqual ← (1=≢)∪
allEqual ← (1≥≢)(⊣⌸⊢)
allEqual ← ⌊/=⌈/ 
allEqual ← ∧/2=/⊢
allEqual ← (((⊃=⊢)⊢⍤/⊢)≡⊢)
allEqual ← ((≢⊢⍤/⊃)≡⊢)

allEqual ← ⊃=.∧⊢ ⍝ Thanks to Aaron Hsu
