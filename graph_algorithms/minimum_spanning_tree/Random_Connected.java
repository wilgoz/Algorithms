import java.util.Random;

public class Random_Connected extends Graph
{
    public Random_Connected(int size)
    {
        super(size);
    }

    private boolean is_connected(Util.Disjoint_Sets set)
    {
        for (int i = 0; i < super.size; i++)
            for (int j = i; j < super.size; j++)
                if (set.find(i) != set.find(j))
                    return false;
        return true;
    }

    @Override
    protected void init_matrix()
    {
        // Initialize |V| forests
        for (int i = 0; i < super.size; i++)
            for (int j = i; j < super.size; j++)
            {
                super.graph[i][j] = 0;
                super.graph[j][i] = 0;
            }

        var rng = new Random();
        var set = new Util.Disjoint_Sets(super.size);

        // Adds random edges until the graph is connected
        while (!is_connected(set))
        {
            int i = rng.nextInt(super.size);
            int j = rng.nextInt(super.size);

            if (i == j) continue;

            set.union(i, j);
            super.graph[i][j] = super.euclid_dist(i, j);
            super.graph[j][i] = super.graph[i][j];
        }
    }
}