(defn filter-odds [list]
    (filter odd? list))

(def list [1 2 3 4 5])

(println (filter-odds list))
