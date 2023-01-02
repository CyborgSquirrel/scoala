using ConsoleApp1.domain;
using ConsoleApp1.repo;

namespace ConsoleApp1.srv;

public class SrvMeci
{
    private IRepo<JucatorActivID, JucatorActiv> repoJucatorActiv;
    private IRepo<Guid, Meci> repoMeci;

    public SrvMeci(IRepo<JucatorActivID, JucatorActiv> repoJucatorActiv, IRepo<Guid, Meci> repoMeci)
    {
        this.repoJucatorActiv = repoJucatorActiv;
        this.repoMeci = repoMeci;
    }

    public Meci[] GetMeciuriInPerioadaCalendaristica(DateOnly inceput, DateOnly sfarsit)
    {
        return repoMeci.GetAll()
            .Where(meci => meci.data >= inceput & meci.data <= sfarsit)
            .ToArray();
    }

    public uint GetScorMeci(Guid meciId)
    {
        repoMeci.Find(meciId);
        return (uint) repoJucatorActiv.GetAll()
            .Where(jucatorActiv => jucatorActiv.id.idMeci == meciId)
            .Sum(jucatorActiv => jucatorActiv.nrPuncteInscrise);
    }
}