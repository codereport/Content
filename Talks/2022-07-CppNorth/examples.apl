    ⍝ Discovering APL
    ⍳5
1 2 3 4 5
    +/⍳5
15
    +\⍳5
1 3 6 10 15

    ⍝ filterOutHTMLTages
    filterOutHTMLTags ← {⍵/⍨(~⊢∨≠\)⍵∊'<>'}
    filterOutHTMLTags '<div>Hello <b>C++North!</b></div>'
'Hello C++North!'

    ⍝ countLRUD
    countLRUD ← {+/'LRUD'∘.=⍵}
    countLRUD 'LRDLURDLURDULR' 
4 4 3 3
