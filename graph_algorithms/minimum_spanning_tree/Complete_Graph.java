public class Complete_Graph extends Graph
{
    public Complete_Graph(int size)
    {
        super(size);
    }

    @Override
    protected void init_matrix()
    {
        for (int i = 0; i < super.size; i++)
            for (int j = i; j < super.size; j++)
            {
                if (i == j)
                {
                    super.graph[i][j] = 0;
                    continue;
                }
                super.graph[i][j] = super.euclid_dist(i, j);
                super.graph[j][i] = super.graph[i][j];
            }
    }
}