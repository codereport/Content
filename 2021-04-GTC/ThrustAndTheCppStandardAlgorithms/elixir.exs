# Elixir solution to copy_if C++ / Thrust code
owners = ["Ahswin", "Lesley", "Sarah"]
pets   = ["Dog",    "Cat",    "Dog"  ]

dogOwners = Enum.zip   (owners, pets) 
         |> Enum.filter(fn {_, pet} -> pet == "Dog" end)
         |> Enum.map   (fn {owner, _} -> owner end)
