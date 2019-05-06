public abstract class Graph
{
    protected int        size;
    private   double[]   x, y;
    protected double[][] graph;

    public Graph(int size)
    {
        this.size   = size;
        this.x      = new double[size];
        this.y      = new double[size];
        this.graph  = new double[size][size];

        // Initialize xy coords within [0, 1]
        for (int i = 0; i < size; i++)
        {
            this.x[i] = Math.random();
            this.y[i] = Math.random();
        }

        this.init_matrix();
    }

    // Weight denoted by the euclid distance between 2 points
    protected double euclid_dist(int i, int j)
    {
        double ydist = Math.abs(this.y[i] - this.y[j]);
        double xdist = Math.abs(this.x[i] - this.x[j]);
        return Math.sqrt((ydist*ydist) + (xdist*xdist));
    }

    protected abstract void init_matrix();

    public int get_size() { return this.size; }
    public double[][] get_graph() { return this.graph; }
}