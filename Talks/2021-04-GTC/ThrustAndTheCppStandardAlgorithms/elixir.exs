# Elixir solution to copy_if C++ / Thrust code
owners = ["Ahswin", "Lesley", "Sarah"]
pets   = ["Dog",    "Cat",    "Dog"  ]

dogOwners = owners 
    |> Enum.zip   (pets) 
    |> Enum.filter(fn {_, pet} -> pet == "Dog" end)
    |> Enum.map   (fn {owner, _} -> owner end)

# Sum Evens
vals = [42, 1729, 4104]

sum_evens = vals 
    |> Enum.filter(&Integer.is_even/1) 
    |> Enum.sum
