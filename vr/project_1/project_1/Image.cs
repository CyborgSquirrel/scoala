using System.Drawing;
using System.Drawing.Imaging;
using SkiaSharp;

namespace rt
{
    public class Image
    {
        private SKBitmap bitmap;

        public Image(int width, int height) {
            bitmap = new SKBitmap(width, height);
        }

        public void SetPixel(int x, int y, Color c) {
            bitmap.SetPixel(x, y, c.ToSystemColor());
        }

        public void Store(string filename)
        {
            var bitmapEncoded = bitmap.Encode(SKEncodedImageFormat.Png, 0);

            using (var fileStream = new FileStream(filename, FileMode.OpenOrCreate, FileAccess.Write))
            {
                bitmapEncoded.SaveTo(fileStream);
            }
        }
    }
}