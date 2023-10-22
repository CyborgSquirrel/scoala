using System;
using System.Runtime.InteropServices;

namespace rt
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            var u = n * viewPlaneSize / imgSize;
            u -= viewPlaneSize / 2;
            return u;
        }

        private Intersection FindFirstIntersection(Line ray, double minT, double maxT)
        {
            var intersection = new Intersection();

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minT, maxT);
                intersection = intersection.GetBest(intr);
            }

            return intersection;
        }

        private bool IsLit(Vector point, Light light)
        {
            // ADD CODE HERE: Detect whether the given point has a clear line of sight to the given light
            return true;
        }

        public void Render(Camera camera, int sizeX, int sizeY, string filename)
        {
            var image = new Image(sizeX, sizeY);

            var viewX = (camera.Up ^ camera.Direction).Normalize();
            var viewY = camera.Up;
            
            // front plane
            var frontPlanePoint = camera.Position + camera.Direction * camera.FrontPlaneDistance;
            var frontPlaneAbc = camera.Direction;
            var frontPlaneD = -(frontPlanePoint * camera.Direction);
            
            // back plane
            var backPlanePoint = camera.Position + camera.Direction * camera.BackPlaneDistance;
            var backPlaneAbc = camera.Direction;
            var backPlaneD = -(backPlanePoint * camera.Direction);
            
            for (var x = 0; x < sizeX; x++)
            {
                for (var y = 0; y < sizeY; y++)
                {
                    // figure out position on view plane
                    var viewPlanePos = (
                            camera.Position
                            + camera.Direction * camera.ViewPlaneDistance
                            + viewX * (((float)x + 0.5) / (float)sizeX - 0.5) * camera.ViewPlaneWidth
                            + viewY * (((float)y + 0.5) / (float)sizeY - 0.5) * camera.ViewPlaneHeight
                            );

                    var ray = new Line(camera.Position, viewPlanePos);

                    // calculate t of intersection between ray and front/back plane, for culling
                    var minT = -(frontPlaneAbc * camera.Position + frontPlaneD) / (frontPlaneAbc * ray.Dx);
                    var maxT = -(backPlaneAbc * camera.Position + backPlaneD) / (backPlaneAbc * ray.Dx);

                    var intersection = FindFirstIntersection(ray, minT, maxT);

                    var color = new Color(0, 0, 0, 1);
                    if (intersection.IsUseable())
                    {
                        var material = intersection.Geometry.Material;

                        var toCamera = (camera.Position - intersection.Position).Normalize();
                        var surfaceNormal = intersection.Normal;

                        // color = intersection.Geometry.Color;

                        if (true)
                        {
                            foreach (var light in lights)
                            {
                                var rayToLight = new Line(intersection.Position, light.Position);
                                // TODO: Ideally maxT should be infinite or something.
                                var lightIntersection = FindFirstIntersection(rayToLight, 0.01, 10000);
                                if (lightIntersection.IsUseable())
                                {
                                    continue;
                                }
                                
                                var toLight = (light.Position - intersection.Position).Normalize();
                                var toLightReflected = surfaceNormal * (surfaceNormal * toLight) * 2 - toLight;

                                var lightColor = new Color();
                                lightColor = material.Ambient * light.Ambient;

                                var diffuseCoef = surfaceNormal * toLight;
                                if (diffuseCoef > 0)
                                {
                                    lightColor += material.Diffuse * light.Diffuse * diffuseCoef;
                                }

                                var specularCoef = toCamera * toLightReflected;
                                if (specularCoef > 0)
                                {
                                    lightColor += material.Specular * light.Specular *
                                                  Math.Pow(specularCoef, material.Shininess);
                                }

                                lightColor *= light.Intensity;

                                color = new Color(
                                    Double.Max(color.Red, lightColor.Red),
                                    Double.Max(color.Green, lightColor.Green),
                                    Double.Max(color.Blue, lightColor.Blue),
                                    Double.Max(color.Alpha, lightColor.Alpha)
                                );
                            }
                        }
                    }
                    
                    image.SetPixel(x, y, color);
                }
            }
            
            image.Store(filename);
        }
    }
}