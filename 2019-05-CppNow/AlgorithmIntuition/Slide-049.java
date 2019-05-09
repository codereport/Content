public static int solve() { 
    List<Integer> l = Arrays.asList( 2, 1, 5, 3, 4 ); 
    int a = Collections.min(l); 
    int b = Collections.max(l); 
    return b - a; 
} 
