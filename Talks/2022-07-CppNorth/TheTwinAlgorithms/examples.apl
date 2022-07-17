    ⍝ Discovering APL
    ⍳5
1 2 3 4 5
    +/⍳5
15
    +\⍳5
1 3 6 10 15

    ⍝ C++ Algorithms
    iota                ← ⍳
    accumulate          ← +/
    partial_sum         ← +\
    inner_product       ← +.×
    adjacent_difference ← 2-⍨/

    min_element    ← ⌊/
    max_element    ← ⌈/
    minmax_element ← ⌊/,⌈/

    any_of  ← {∨/⍺⍺⍵}
    all_of  ← {∧/⍺⍺⍵}
    none_of ← {~∨/⍺⍺⍵}

    count    ← {+/⍺=⍵}
    count_if ← {+/⍺⍺⍵}

    reverse ← ⌽ 
    rotate  ← ⌽ 

    ⍝ filterOutHTMLTages
    filterOutHTMLTags ← {⍵/⍨(~⊢∨≠\)⍵∊'<>'}
    filterOutHTMLTags '<div>Hello <b>C++North!</b></div>'
'Hello C++North!'

    ⍝ countLRUD
    countLRUD ← {+/'LRUD'∘.=⍵}
    countLRUD 'LRDLURDLURDULR' 
4 4 3 3
