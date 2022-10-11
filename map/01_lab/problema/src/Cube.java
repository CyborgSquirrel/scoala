public class Cube extends Square {
    public Cube(float size) {
        super(size);
    }
    @Override
    public float area() {
        return super.area()*6;
    }
}