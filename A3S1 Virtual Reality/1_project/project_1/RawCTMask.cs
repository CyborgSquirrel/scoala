using System;
using System.IO;
using System.Numerics;
using System.Text.RegularExpressions;

namespace rt;

public class RawCtMask: Geometry
{
    // private const double ALPHA_COEF_THRESH = 0.1;
    private const double ALPHA_COEF_THRESH = 0.01;
    
    private const double T_INCREMENT = 0.1;
    // private const double T_INCREMENT = 1;
    
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0;
    private readonly Vector _v1;
    
    private readonly AAPlane[] _planes;

    public RawCtMask(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) : base(Color.NONE)
    {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines)
        {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution")
            {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            } else if (kv[0] == "SliceThickness")
            {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        _v1 = position + new Vector(_resolution[0]*_thickness[0]*scale, _resolution[1]*_thickness[1]*scale, _resolution[2]*_thickness[2]*scale);

        _planes = new[]
        {
            AAPlane.FromNormalAndPoints(
                new Vector(0, 0, -1),
                new Vector(_v0.X, _v0.Y, _v0.Z),
                new Vector(_v1.X, _v1.Y, _v0.Z)),
            AAPlane.FromNormalAndPoints(
                new Vector(0, 0, 1),
                new Vector(_v0.X, _v0.Y, _v1.Z),
                new Vector(_v1.X, _v1.Y, _v1.Z)),
            AAPlane.FromNormalAndPoints(
                new Vector(-1, 0, 0),
                new Vector(_v0.X, _v0.Y, _v0.Z),
                new Vector(_v0.X, _v1.Y, _v1.Z)),
            AAPlane.FromNormalAndPoints(
                new Vector(1, 0, 0),
                new Vector(_v1.X, _v0.Y, _v0.Z),
                new Vector(_v1.X, _v1.Y, _v1.Z)),
            AAPlane.FromNormalAndPoints(
                new Vector(0, -1, 0),
                new Vector(_v0.X, _v0.Y, _v0.Z),
                new Vector(_v1.X, _v0.Y, _v1.Z)),
            AAPlane.FromNormalAndPoints(
                new Vector(0, 1, 0),
                new Vector(_v0.X, _v1.Y, _v0.Z),
                new Vector(_v1.X, _v1.Y, _v1.Z)),
        };
        
        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len)
        {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }
    }

    private bool IsInside(Vector v)
    {
        // JetBrains' Rider auto formatting was being uncooperative. Therefore "true &&" has been added.
        return true && v.X >= _v0.X && v.X <= _v1.X
               && v.Y >= _v0.Y && v.Y <= _v1.Y
               && v.Z >= _v0.Z && v.Z <= _v1.Z;
    }
    
    private ushort Value(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
        {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }

    public override Intersection GetIntersection(Line line, double minT, double maxT)
    {
        bool cubeIntersection = false;
        double minCubeT = 0;
        double maxCubeT = 0;
        foreach (var plane in _planes)
        {
            // NOTE: This also ought to be infinte or something.
            var intersection = plane.GetIntersection(line, -1_000_000, 1_000_000);
            if (intersection.IsUseable())
            {
                if (!cubeIntersection)
                {
                    cubeIntersection = true;
                    minCubeT = intersection.T;
                    maxCubeT = intersection.T;
                }
                else
                {
                    minCubeT = Double.Min(minCubeT, intersection.T);
                    maxCubeT = Double.Max(maxCubeT, intersection.T);
                }
            }
        }
        
        if (!cubeIntersection) return Intersection.NONE;
        if (maxCubeT < minT || minCubeT > maxT) return Intersection.NONE;

        double t = Double.Max(minT, minCubeT);
        double iterT = t;
        double alphaCoefAcc = 1;
        Color colorAcc = new Color(0, 0, 0, 1);
        while (alphaCoefAcc > ALPHA_COEF_THRESH)
        {
            if (iterT > maxCubeT)
            {
                // NOTE: Seems kind of sus.
                return Intersection.NONE;
                break;
            }
            
            Vector pos = line.CoordinateToPosition(iterT);
            Color color = GetColor(pos);
            double alphaCoef = color.Alpha;
            colorAcc += color * alphaCoef * alphaCoefAcc;
            alphaCoefAcc *= 1 - alphaCoef;

            t = iterT;
            iterT += T_INCREMENT;
        }

        // if (alphaCoefAcc < 0.01)
        // {
        //     return Intersection.NONE;
        // }

        {
            Vector pos = line.CoordinateToPosition(t);
            return new Intersection(
                minT, maxT, this, line, t, GetNormal(pos), Material.fromColor(colorAcc), colorAcc);
        }
    }
    
    private int[] GetIndexes(Vector v)
    {
        return new []{
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale), 
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)};
    }
    private Color GetColor(Vector v)
    {
        int[] idx = GetIndexes(v);

        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(Vector v)
    {
        int[] idx = GetIndexes(v);
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}