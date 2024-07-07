namespace ConsoleApp1.domain;

public class Jucator : Elev
{
    public Guid echipaId { get; }

    public Jucator(Guid id, string nume, string scoala, Guid echipaId) : base(id, nume, scoala)
    {
        this.echipaId = echipaId;
    }
}