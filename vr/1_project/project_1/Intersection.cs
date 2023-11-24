namespace rt
{
    public class Intersection
    {
        public static readonly Intersection NONE = new();
        
        public bool Valid{ get; set; }
        public bool Visible{ get; set; }
        public double T{ get; }
        public Vector Position{ get; }
        public Geometry Geometry{ get; set; }
        public Line Line{ get; }

        public Vector Normal { get; }
        public Material Material { get; set; }
        public Color Color { get; set; }
        
        public Intersection() {
            Geometry = null;
            Line = null;
            Valid = false;
            Visible = false;
            T = 0;
            Position = null;
            Normal = null;
            Material = new();
            Color = new();
        }

        public Intersection(double minT, double maxT, Line line, double t, Vector normal)
        {
            Line = line;
            Valid = true;
            T = t;
            Position = Line.CoordinateToPosition(t);
            Visible = T >= minT && T <= maxT;
            Normal = normal;
        }

        public Intersection(double minT, double maxT, Geometry geometry, Line line, double t, Vector normal, Material material, Color color) {
            Geometry = geometry;
            Line = line;
            Valid = true;
            T = t;
            Visible = T >= minT && T <= maxT;
            Position = Line.CoordinateToPosition(t);
            Normal = normal;
            Material = material;
            Color = color;
        }

        public bool IsUseable()
        {
            return Valid && Visible;
        }

        public Intersection GetBest(Intersection other)
        {
            Intersection a = this;
            Intersection b = other;

            if (a.IsUseable() && b.IsUseable())
            {
                if (a.T < b.T)
                {
                    return a;
                }
                else
                {
                    return b;
                }
            }
            else if (a.IsUseable())
            {
                return a;
            }
            else if (b.IsUseable())
            {
                return b;
            }
            else
            {
                // NOTE: Ideally maybe shouldn't return anything here, but what can u do :L .
                return a;
            }
        }
    }
}