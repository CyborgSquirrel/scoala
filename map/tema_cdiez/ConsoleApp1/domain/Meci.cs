namespace ConsoleApp1.domain;

public class Meci : Entity<Guid>
{
    public Meci(Guid id, Guid echipa1Id, Guid echipa2Id, DateOnly data)
    {
        this.id = id;
        this.echipa1Id = echipa1Id;
        this.echipa2Id = echipa2Id;
        this.data = data;
    }

    public Guid id { get; }
    public Guid echipa1Id { get; }
    public Guid echipa2Id { get; }
    public DateOnly data { get; }
}