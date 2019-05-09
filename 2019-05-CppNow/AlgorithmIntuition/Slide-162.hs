dangerous_teams :: String -> Bool 
dangerous_teams = (>=7) 
                . maximum 
                . map length 
                . group 
