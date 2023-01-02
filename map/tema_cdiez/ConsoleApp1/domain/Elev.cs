namespace ConsoleApp1.domain;

public class Elev : Entity<Guid>
{
    public Guid id { get; }
    public string nume { get; }
    public string scoala { get; }

    public Elev(Guid id, string nume, string scoala)
    {
        this.id = id;
        this.nume = nume;
        this.scoala = scoala;
    }
}

