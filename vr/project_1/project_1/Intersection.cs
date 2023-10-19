namespace rt
{
    public class Intersection
    {
        public bool Valid{ get; set; }
        public bool Visible{ get; set; }
        public double T{ get; set; }
        public Vector Position{ get; set; }
        public Geometry Geometry{ get; set; }
        public Line Line{ get; set; }

        public Intersection() {
            Geometry = null;
            Line = null;
            Valid = false;
            Visible = false;
            T = 0;
            Position = null;
        }

        public Intersection(double minT, double maxT, Geometry geometry, Line line, double t) {
            Geometry = geometry;
            Line = line;
            Valid = true;
            T = t;
            Visible = T >= minT && T <= maxT;
            Position = Line.CoordinateToPosition(t);
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