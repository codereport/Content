⍝ APL solution to copy_if C++ / Thrust code
      owners ← 'Ashwin' 'Lesley' 'Sarah'
      pets   ← 'Dog'    'Cat'    'Dog'
      'Dog'∘≡¨pets
1 0 1
      ('Dog'∘≡¨pets)/owners
┌──────┬─────┐
│Ashwin│Sarah│
└──────┴─────┘
