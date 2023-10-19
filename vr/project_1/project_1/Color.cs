using System;
using SkiaSharp;

namespace rt
{
    public class Color
    {
        public double Red { get; set; }
        public double Green { get; set; }
        public double Blue { get; set; }
        public double Alpha { get; set; }

        public Color()
        {
            Red = 0;
            Green = 0;
            Blue = 0;
            Alpha = 0;
        }

        public Color(double red, double green, double blue, double alpha)
        {
            Red = red;
            Green = green;
            Blue = blue;
            Alpha = alpha;
        }

        public Color(Color c)
        {
            Red = c.Red;
            Green = c.Green;
            Blue = c.Blue;
            Alpha = c.Alpha;
        }

        public SKColor ToSystemColor()
        {
            var r = Convert.ToByte(Math.Min((int)Math.Ceiling(Red * 255), 255));
            var g = Convert.ToByte(Math.Min((int)Math.Ceiling(Green * 255), 255));
            var b = Convert.ToByte(Math.Min((int)Math.Ceiling(Blue * 255), 255));
            var a = Convert.ToByte(Math.Min((int)Math.Ceiling(Alpha * 255), 255));

            return new SKColor(r, g, b, a);
        }

        public static Color operator +(Color a, Color b)
        {
            return new Color(a.Red + b.Red, a.Green + b.Green, a.Blue + b.Blue, a.Alpha + b.Alpha);
        }

        public static Color operator -(Color a, Color b)
        {
            return new Color(a.Red - b.Red, a.Green - b.Green, a.Blue - b.Blue, a.Alpha - b.Alpha);
        }

        public static Color operator *(Color a, Color b)
        {
            return new Color(a.Red * b.Red, a.Green * b.Green, a.Blue * b.Blue, a.Alpha * b.Alpha);
        }

        public static Color operator /(Color a, Color b)
        {
            return new Color(a.Red / b.Red, a.Green / b.Green, a.Blue / b.Blue, a.Alpha / b.Alpha);
        }

        public static Color operator *(Color c, double k)
        {
            return new Color(c.Red * k, c.Green * k, c.Blue * k, c.Alpha * k);
        }

        public static Color operator /(Color c, double k)
        {
            return new Color(c.Red / k, c.Green / k, c.Blue / k, c.Alpha / k);
        }

        public override string ToString()
        {
            return $"{nameof(Red)}: {Red}, {nameof(Green)}: {Green}, {nameof(Blue)}: {Blue}, {nameof(Alpha)}: {Alpha}";
        }
    }
}