let list = [1; 2; 3; 4; 5];;

let filterOdds l = List.filter (fun x -> x mod 2 != 0) l ;;

filterOdds list
