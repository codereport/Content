; Solution 1

(defn is-special-array [nums]
  (->> nums
       (partition 2 1)
       (map #(reduce not= %))
       (every? identity)))

; Solution 2
(defn is-special-array [nums]
  (->> nums
       (partition 2 1)
       (every? (fn [[a b]] not= a b))))
