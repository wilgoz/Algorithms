import java.util.*;

public class MST
{
    private static final int   MAX_ITER  =   50;
    private static final int[] MAX_NODES = { 100, 500, 1000, 5000 };

    public static void main(String[] args)
    {
        for (int nodes : MAX_NODES)
        {
            long prim_stime, prim_etime, prim_rtime = 0;
            long krus_stime, krus_etime, krus_rtime = 0;

            double prim_cost = 0;
            double krus_cost = 0;

            for (int i = 0; i < MAX_ITER; i++)
            {
                // Graph graph = new Random_Connected(nodes);
                Graph graph = new Complete_Graph(nodes);

                // Prim's Benchmark
                prim_stime  = System.nanoTime();
                prim_cost  += prim_weight(graph);
                prim_etime  = System.nanoTime();
                prim_rtime += (prim_etime - prim_stime);

                // Kruskal's Benchmark
                krus_stime  = System.nanoTime();
                krus_cost  += kruskal_weight(graph);
                krus_etime  = System.nanoTime();
                krus_rtime += (krus_etime - krus_stime);
            }

            System.out.println("[PRIM'S]");
            System.out.println("Nodes: "       + nodes                 + ", " +
                               "Avg Weight: "  + prim_cost  / MAX_ITER + ", " +
                               "Avg Runtime: " + prim_rtime / MAX_ITER + " ns");
            System.out.println("[KRUSKAL'S]");
            System.out.println("Nodes: "       + nodes                 + ", " +
                               "Avg Weight: "  + krus_cost  / MAX_ITER + ", " +
                               "Avg Runtime: " + krus_rtime / MAX_ITER + " ns\n");
        }
    }

    private static double prim_weight(Graph g)
    {
        int size = g.get_size();
        double cost = 0;
        boolean[] visited = new boolean[size];

        var edge = new Util.Edge[size];
        double[][] graph = g.get_graph();

        // Initializes paths with INF costs to every vertices
        // Let vertex 0 be the source vertex
        for (int i = 0; i < size; i++)
            edge[i] = new Util.Edge(i, Double.MAX_VALUE);
        edge[0].set_weight(0);

        // Initialize the min-heap with all paths
        var min_heap = new PriorityQueue<Util.Edge>();
        for (int i = 0; i < size; i++)
            min_heap.add(edge[i]);

        while (!min_heap.isEmpty())
        {
            Util.Edge min = min_heap.poll();

            visited[min.get_dst()] = true;
            cost += min.get_weight();

            // Updates the weights of adjacent vertices
            // No UPDATE_KEY sadly
            for (int i = 0; i < size; i++)
                if (graph[min.get_dst()][i] != 0
                    && !visited[i]
                    && graph[min.get_dst()][i] < edge[i].get_weight())
                {
                    min_heap.remove(edge[i]);
                    edge[i].set_weight(graph[min.get_dst()][i]);
                    min_heap.add(edge[i]);
                }
        }
        return cost;
    }

    private static double kruskal_weight(Graph g)
    {
        int size = g.get_size();
        int components = size;
        double[][] graph = g.get_graph();
        double cost = 0;

        var set = new Util.Disjoint_Sets(size);
        var min_heap = new PriorityQueue<Util.Edge>();

        // Adds all edges to the min-heap; O(E)
        for (int i = 0; i < size; i++)
            for (int j = i; j < size; j++)
                if (graph[i][j] > 0)
                    min_heap.add(new Util.Edge(i, j, graph[i][j]));

        // Unify disjoint sets until a single component is formed
        while (!min_heap.isEmpty() && components != 1)
        {
            // Only takes light edges that will not cause cycles
            Util.Edge min = min_heap.poll();
            if (set.find(min.get_src()) != set.find(min.get_dst()))
            {
                components--;
                cost += min.get_weight();
                set.union(min.get_src(), min.get_dst());
            }
        }
        return cost;
    }
}
