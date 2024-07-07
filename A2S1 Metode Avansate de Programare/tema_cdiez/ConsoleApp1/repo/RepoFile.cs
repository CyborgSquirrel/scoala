using System.Runtime.Serialization.Formatters.Binary;
using System.Text.Json;
using ConsoleApp1.domain;

namespace ConsoleApp1.repo;

public class RepoFile<ID, E> : IRepo<ID, E>
where E: Entity<ID> where ID : notnull
{
    private Dictionary<ID, E> dictionary;
    private string filePath;

    private void ReadAllFromFile()
    {
        try
        {
            var file = File.Open(filePath, FileMode.Open);
            var options = new JsonSerializerOptions();
            options.Converters.Add(new DateOnlyConverter());
            options.Converters.Add(new JucatorActivIDConverter());
            dictionary = JsonSerializer.Deserialize<Dictionary<ID, E>>(file, options) ??
                         throw new InvalidOperationException();
            file.Close();
        }
        catch (System.IO.FileNotFoundException)
        {
            // do nothing
        }
    }

    private void WriteAllToFile()
    {
        var file = File.Open(filePath, FileMode.Create);
        var options = new JsonSerializerOptions();
        options.Converters.Add(new DateOnlyConverter());
        options.Converters.Add(new JucatorActivIDConverter());
        JsonSerializer.Serialize(file, dictionary, options);
        file.Close();
    }

    public RepoFile(string filePath)
    {
        this.dictionary = new Dictionary<ID, E>();
        this.filePath = filePath;
        ReadAllFromFile();
    }


    public void Store(E e)
    {
        if (dictionary.ContainsKey(e.id))
        {
            throw new EntityAlreadyExistsException();
        }
        dictionary.Add(e.id, e);
        WriteAllToFile();
    }

    public void Update(E e)
    {
        if (!dictionary.ContainsKey(e.id))
        {
            throw new EntityDoesntExistException();
        }
        dictionary.Add(e.id, e);
        WriteAllToFile();
    }

    public E Find(ID id)
    {
        if (!dictionary.ContainsKey(id))
        {
            throw new EntityDoesntExistException();
        }

        return dictionary[id];
    }

    public void Erase(ID id)
    {
        if (!dictionary.ContainsKey(id))
        {
            throw new EntityDoesntExistException();
        }

        dictionary.Remove(id);
    }

    public E[] GetAll()
    {
        return dictionary.Values.ToArray();
    }
}