// See https://aka.ms/new-console-template for more information

using System.Drawing;
using System.Globalization;
using System.Runtime.CompilerServices;
using ConsoleApp1.domain;
using ConsoleApp1.repo;
using ConsoleApp1.srv;

// REPO
var repoElev = new RepoFile<Guid, Elev>("./elev.json");
var repoEchipa = new RepoFile<Guid, Echipa>("./echipa.json");
var repoJucator = new RepoFile<Guid, Jucator>("./jucator.json");
var repoJucatorActiv = new RepoFile<JucatorActivID, JucatorActiv>("./jucatorActiv.json");
var repoMeci = new RepoFile<Guid, Meci>("./meci.json");

// SRV
var srvEchipa = new SrvEchipa(repoJucator, repoJucatorActiv, repoEchipa, repoMeci);
var srvMeci = new SrvMeci(repoJucatorActiv, repoMeci);

repoJucatorActiv.Store(new JucatorActiv(new JucatorActivID(Guid.Parse("fe9aff41-56b2-4350-b735-a475ee3cd2fb"), Guid.Parse("7ae8c753-b980-4282-b240-05f132700f8a")), 12, TipJucator.Participant));

bool running = true;

while (running)
{
    Console.WriteLine("0. Exit");
    Console.WriteLine("1. Afiseaza toti jucatorii unei echipe date");
    Console.WriteLine("2. Afiseaza toti jucatorii activi ai unei echipe de la un anumit meci");
    Console.WriteLine("3. Afiseaza toate meciurile dintr-o anumita perioada calendaristica");
    Console.WriteLine("4. Afiseaza scorul de la un anumit meci");
    
    uint choice = uint.Parse(Console.ReadLine());
    switch (choice)
    {
        case 0:
        {
            running = false;
            break;
        }
        case 1:
        {
            Console.Write("echipa id = ");
            var echipaId = Guid.Parse(Console.ReadLine());
            var jucatoriEchipa = srvEchipa.GetJucatoriEchipa(echipaId);
            foreach (var jucator in jucatoriEchipa)
            {
                Console.WriteLine($"\"{jucator.nume}\" \"{jucator.scoala}\"");
            }

            break;
        }
        case 2:
        {
            Console.Write("meci id = ");
            var meciId = Guid.Parse(Console.ReadLine());
            Console.Write("echipa id = ");
            var echipaId = Guid.Parse(Console.ReadLine());
            var jucatoriActiviAiEchipeiLaMeci = srvEchipa.GetJucatoriActiviAiEchipeiLaMeci(meciId, echipaId);
            foreach (var jucator in jucatoriActiviAiEchipeiLaMeci)
            {
                Console.WriteLine($"\"{jucator.nume}\" \"{jucator.scoala}\"");
            }
            
            break;
        }
        case 3:
        {
            Console.Write("inceput (dd/mm/yyyy) = ");
            var inceput = DateOnly.ParseExact(Console.ReadLine(), "dd/MM/yyyy");
            Console.Write("sfarsit (dd/mm/yyyy) = ");
            var sfarsit = DateOnly.ParseExact(Console.ReadLine(), "dd/MM/yyyy");
            var meciuriInPerioadaCalendaristica = srvMeci.GetMeciuriInPerioadaCalendaristica(inceput, sfarsit);
            foreach (var meci in meciuriInPerioadaCalendaristica)
            {
                Console.WriteLine($"\"{meci.echipa1Id}\" \"{meci.echipa2Id}\" \"{meci.data}\"");
            }
            
            break;
        }
        case 4:
        {
            Console.Write("meci id = ");
            var meciId = Guid.Parse(Console.ReadLine());
            var scorMeci = srvMeci.GetScorMeci(meciId);
            Console.WriteLine($"Scorul este {scorMeci}.");
            
            break;
        }
    }
}