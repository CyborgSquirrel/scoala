namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minT, double maxT)
        {
            double Af(double lineDxX, double semiAxesLengthX)
            {
                return Math.Pow(lineDxX, 2) / Math.Pow(semiAxesLengthX, 2);
            }
            var a = 
                + Af(line.Dx.X, SemiAxesLength.X)
                + Af(line.Dx.Y, SemiAxesLength.Y)
                + Af(line.Dx.Z, SemiAxesLength.Z);

            double Bf(double lineX0X, double lineDxX, double sphereCenterX, double semiAxesLengthX)
            {
                return (2 * lineDxX * (lineX0X - sphereCenterX)) / Math.Pow(semiAxesLengthX, 2);
            }
            var b =
                + Bf(line.X0.X, line.Dx.X, Center.X, SemiAxesLength.X)
                + Bf(line.X0.Y, line.Dx.Y, Center.Y, SemiAxesLength.Y)
                + Bf(line.X0.Z, line.Dx.Z, Center.Z, SemiAxesLength.Z);

            double Cf(double lineX0X, double sphereCenterX, double semiAxesLengthX)
            {
                return Math.Pow(lineX0X - sphereCenterX, 2) / Math.Pow(semiAxesLengthX, 2);
            }
            var c =
                + Cf(line.X0.X, Center.X, SemiAxesLength.X)
                + Cf(line.X0.Y, Center.Y, SemiAxesLength.Y)
                + Cf(line.X0.Z, Center.Z, SemiAxesLength.Z)
                - Math.Pow(Radius, 2);

            var delta = b * b - 4 * a * c;
            if (delta >= 0)
            {
                var deltaSqrt = Math.Sqrt(delta);
                var t1 = (-b + deltaSqrt) / (2 * a);
                var t2 = (-b - deltaSqrt) / (2 * a);

                var v1 = line.CoordinateToPosition(t1);
                var v2 = line.CoordinateToPosition(t2);

                var n1 = (v1 - Center).Divide(SemiAxesLength.Multiply(SemiAxesLength)) * 2;
                var n2 = (v2 - Center).Divide(SemiAxesLength.Multiply(SemiAxesLength)) * 2;

                n1.Normalize();
                n2.Normalize();
                
                var i1 = new Intersection(minT, maxT, this, line, t1, n1, Material, Color);
                var i2 = new Intersection(minT, maxT, this, line, t2, n2, Material, Color);

                return i1.GetBest(i2);
            }

            return new Intersection();
        }
    }
}