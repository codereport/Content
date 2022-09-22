(defn filter-odds [list]
    (filter odd? list))

(defn filter-odds1 [list]
    (filter #(= 1 (mod % 2)) list))

(def list [1 2 3 4 5])

(println (filter-odds list))
(println (filter-odds1 list))
