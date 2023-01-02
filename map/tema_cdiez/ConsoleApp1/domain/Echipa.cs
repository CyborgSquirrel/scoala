namespace ConsoleApp1.domain;

public class Echipa : Entity<Guid>
{
    public Guid id { get; }
    public string nume { get; }

    public Echipa(Guid id, string nume)
    {
        this.id = id;
        this.nume = nume;
    }
}