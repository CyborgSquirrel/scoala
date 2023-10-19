using System;

namespace rt
{
    public class Sphere : Geometry
    {
        private Vector Center { get; set; }
        private double Radius { get; set; }

        public Sphere(Vector center, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minT, double maxT)
        {
            double Af(double lineDxX)
            {
                return lineDxX * lineDxX;
            }
            var a = 
                + Af(line.Dx.X)
                + Af(line.Dx.Y)
                + Af(line.Dx.Z);

            double Bf(double lineX0X, double lineDxX, double sphereCenterX)
            {
                return 2 * lineDxX * (lineX0X - sphereCenterX);
            }
            var b =
                + Bf(line.X0.X, line.Dx.X, Center.X)
                + Bf(line.X0.Y, line.Dx.Y, Center.Y)
                + Bf(line.X0.Z, line.Dx.Z, Center.Z);

            double Cf(double lineX0X, double sphereCenterX)
            {
                return (lineX0X - sphereCenterX) * (lineX0X - sphereCenterX);
            }
            var c =
                + Cf(line.X0.X, Center.X)
                + Cf(line.X0.Y, Center.Y)
                + Cf(line.X0.Z, Center.Z)
                - Radius * Radius;

            var delta = b * b - 4 * a * c;
            if (delta >= 0)
            {
                var deltaSqrt = Math.Sqrt(delta);
                var t1 = (-b + deltaSqrt) / (2 * a);
                var t2 = (-b - deltaSqrt) / (2 * a);
                
                var i1 = new Intersection(minT, maxT, this, line, t1);
                var i2 = new Intersection(minT, maxT, this, line, t2);

                return i1.GetBest(i2);
            }

            return new Intersection();
        }

        public override Vector Normal(Vector v)
        {
            var n = v - Center;
            n.Normalize();
            return n;
        }
    }
}