⍝ APL solution to copy_if C++ / Thrust code
      owners ← 'Ashwin' 'Lesley' 'Sarah'
      pets   ← 'Dog'    'Cat'    'Dog'
      'Dog'∘≡¨pets
1 0 1
      ('Dog'∘≡¨pets)/owners
┌──────┬─────┐
│Ashwin│Sarah│
└──────┴─────┘

⍝ APL solution to Sum Evens
      sumEvens ← (~2|⊢)+.×⊢
      sumEvens 42 1729 4104
4146

(~2|⊢)+.×⊢
  ┌──────┼─┐
┌─┴─┐    . ⊢
~ ┌─┼─┐ ┌┴┐ 
  2 | ⊢ + × 
