⍝ Calculating the first 5 Ramanujan (Taxi Cab) Numbers: 1729 4104 13832 20683 32832

⍝ Original solution at 2:40 AM Sept 8, 2020
ram ← (0,2=/t)/t←{⍵[⍋⍵]}(,∘.<⍨⍳33)/,∘.{+/*∘3¨⍺,⍵}⍨⍳33

⍝ 2nd Solution at 10:10 PM Sept 13, 2020 (after finding https://www.jsoftware.com/papers/50/50_17.htm)
ram ← (0,2=/t)/t←{⍵[⍋⍵]}(,∘.<⍨⍳33)/,∘.+⍨*∘3⍳33

⍝ 3rd Solution at 10:17 PM Sept 13, 2020 
ram ← ⊃¨(2=≢¨t)/t←{⊂⍵}⌸⍨(,∘.<⍨⍳33)/,∘.+⍨*∘3⍳33

⍝ 4th Solution at 10:21 PM Sept 13, 2020 
ram ← ⊃¨(2=≢¨t)/t←{⊂⍵}⌸⍨,(∘.<⍨⍳33)×∘.+⍨*∘3⍳33

⍝ Should be a possible solution (△. = triangle product)
ram ← ⊃¨(2=≢¨t)/t←{⊂⍵}⌸⍨,△.+⍨*∘3⍳33
