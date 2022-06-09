   public static int solve(int h, List<Integer> w, List<Integer> l) {
        int p = 0;
        for (int i = 0; i < w.size(); ++i)
            p = Math.max(p, w.get(i) - l.get(i)/4);
        return Math.max(0, p - h);
    }
