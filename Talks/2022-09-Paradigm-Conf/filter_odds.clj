(defn filter-odds [list]
    (filter odd? list))

(defn filter-odds1 [list]
    (filter #(= 1 (mod % 2)) list))

(def list [1 2 3 4 5])

(println (filter-odds list))
(println (filter-odds1 list))

;; Example of threading

(defn sum-first-two-odds [list]
    (reduce + (take 2 (filter odd? list))))

(defn sum-first-two-odds1 [list]
    (->> list
         (filter odd?)
         (take 2)
         (reduce +)))

(println (sum-first-two-odds list))
(println (sum-first-two-odds1 list))
