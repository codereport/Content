import java.util.*;
import java.util.stream.Collectors;

public class MyClass {

    public static List<Integer> filterOdds(List<Integer> list) {
        var res = new ArrayList<Integer>();
        for (var e : list) {
            if (e % 2 == 1) {
                res.add(e);
            }
        }
        return res;
    }

    public static List<Integer> filterOdds1(List<Integer> list) {
        return list.stream()
                   .filter(e -> e % 2 == 1)
                   .collect(Collectors.toList());
    }


    public static void main(String args[]) {

        var list = List.of(1, 2, 3, 4, 5);

        System.out.println(filterOdds (list));
        System.out.println(filterOdds1(list));
    }
}
