⍝ Calculating the first 5 Ramanujan (Taxi Cab) Numbers: 1729 4104 13832 20683 32832
⍝ Original solution at 2:40 AM Sept 8, 2020
ram ← (0,2=/t)/t←{⍵[⍋⍵]}(,∘.<⍨⍳33)/,∘.{+/*∘3¨⍺,⍵}⍨⍳33
