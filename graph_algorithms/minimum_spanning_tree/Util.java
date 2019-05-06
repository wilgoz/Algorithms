public class Util
{
    public static class Edge implements Comparable<Edge>
    {
        private int src, dst;
        private double weight;

        public Edge(int dst, double weight)
        {
            this.dst = dst;
            this.weight = weight;
        }

        public Edge(int src, int dst, double weight)
        {
            this(dst, weight);
            this.src = src;
        }

        public int compareTo(Edge edge)
        {
            return Double.compare(this.weight, edge.weight);
        }

        public int get_src() { return src; }
        public int get_dst() { return dst; }
        public double get_weight() { return weight; }
        public void set_weight(double weight) { this.weight = weight; }
    }

    public static class Disjoint_Sets
    {
        private int[] rank, parent;

        public Disjoint_Sets(int size)
        {
            this.rank   = new int[size];
            this.parent = new int[size];

            for (int i = 0; i < size; i++)
            {
                this.rank  [i] = 0;
                this.parent[i] = i;
            }
        }

        public int find(int x)
        {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }

        // Union by rank + path compression
        public void union(int x, int y)
        {
            int x_root = find(x);
            int y_root = find(y);

            if (x_root == y_root) return;

            // Move sets of a lower rank under that of a higher one
            // If ranks are equal, move either one & increase its rank
            if (this.rank[x_root] < this.rank[y_root])
                parent[x_root] = parent[y_root];
            else if (this.rank[x_root] > this.rank[y_root])
                parent[y_root] = parent[x_root];
            else
            {
                parent[y_root] = parent[x_root];
                rank[x_root]++;
            }
        }
    }
}
