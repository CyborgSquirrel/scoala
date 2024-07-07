namespace rt;

/// <summary>
/// Axis aligned plane.
/// </summary>
public class AAPlane
{
    public Vector Normal { get; set; }
    public double D { get; set; }
    
    public Vector P0 { get; set; }
    public Vector P1 { get; set; }

    private AAPlane()
    {
        
    }
    
    public static AAPlane FromNormalAndPoints(Vector normal, Vector p0, Vector p1)
    {
        AAPlane plane = new();

        plane.Normal = normal;
        plane.D = -(normal * p0);
        
        plane.P0 = p0;
        plane.P1 = p1;
        
        return plane;
    }

    // NOTE: This is kinda a hack.
    public Intersection GetIntersection(Line line, double minT, double maxT)
    {
        double denominator = Normal * line.Dx;
        if (Math.Abs(denominator) <= 0.0001) return Intersection.NONE;

        double numerator = -(Normal * line.X0 + D);
        double t = numerator / denominator;

        Vector s = P1 - P0;
        Vector p = line.CoordinateToPosition(t) - P0;

        bool Check(double Sx, double Px)
        {
            if (Sx <= 0.0001)
            {
                return Math.Abs(Px) <= 0.0001;
            }
            else
            {
                return Px >= 0 && Px <= Sx;
            }
        }

        bool allChecks = Check(s.X, p.X)
                         && Check(s.Y, p.Y)
                         && Check(s.Z, p.Z);
        
        if (!allChecks) return Intersection.NONE;

        return new Intersection(minT, maxT, line, t, Normal);
    }
}