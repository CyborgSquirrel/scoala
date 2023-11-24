using System;

namespace rt
{
    public class Sphere : Ellipsoid
    {
        private Vector Center { get; set; }
        private double Radius { get; set; }

        public Sphere(Vector center, double radius, Color color) : base(center, new Vector(1, 1, 1), radius, color)
        {
            Center = center;
            Radius = radius;
        }
    }
}