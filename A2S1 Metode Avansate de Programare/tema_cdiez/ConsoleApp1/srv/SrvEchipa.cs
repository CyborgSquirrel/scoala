using ConsoleApp1.domain;
using ConsoleApp1.repo;

namespace ConsoleApp1.srv;

public class SrvEchipa
{
    private IRepo<Guid, Jucator> repoJucator;
    private IRepo<JucatorActivID, JucatorActiv> repoJucatorActiv;
    private IRepo<Guid, Echipa> repoEchipa;
    private IRepo<Guid, Meci> repoMeci;

    public SrvEchipa(IRepo<Guid, Jucator> repoJucator, IRepo<JucatorActivID, JucatorActiv> repoJucatorActiv, IRepo<Guid, Echipa> repoEchipa, IRepo<Guid, Meci> repoMeci)
    {
        this.repoJucator = repoJucator;
        this.repoJucatorActiv = repoJucatorActiv;
        this.repoEchipa = repoEchipa;
        this.repoMeci = repoMeci;
    }

    public Jucator[] GetJucatoriEchipa(Guid echipaId)
    {
        repoEchipa.Find(echipaId);
        return repoJucator.GetAll()
            .Where(jucator => jucator.echipaId == echipaId)
            .ToArray();
    }

    public Jucator[] GetJucatoriActiviAiEchipeiLaMeci(Guid meciId, Guid echipaId)
    {
        repoMeci.Find(meciId);
        return repoJucatorActiv.GetAll()
            .Where(jucatorActiv => 
                jucatorActiv.id.idMeci == meciId 
                & repoJucator.Find(jucatorActiv.id.idJucator).echipaId == echipaId)
            .Join(
                repoJucator.GetAll(),
                jucatorActiv => jucatorActiv.id.idJucator,
                jucator => jucator.id,
                ((jucatorActiv, jucator) => jucator))
            .ToArray();
    }
}