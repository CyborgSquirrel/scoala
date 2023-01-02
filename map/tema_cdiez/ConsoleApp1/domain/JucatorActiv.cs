namespace ConsoleApp1.domain;

public class JucatorActivID
{
    public Guid idJucator;
    public Guid idMeci;

    public JucatorActivID(Guid idJucator, Guid idMeci)
    {
        this.idJucator = idJucator;
        this.idMeci = idMeci;
    }
}

public class JucatorActiv : Entity<JucatorActivID>
{
    public JucatorActivID id { get; }
    public uint nrPuncteInscrise { get; }
    public TipJucator tip { get; }

    public JucatorActiv(JucatorActivID id, uint nrPuncteInscrise, TipJucator tip)
    {
        this.id = id;
        this.nrPuncteInscrise = nrPuncteInscrise;
        this.tip = tip;
    }
}

public enum TipJucator
{
    Rezerva,
    Participant,
}