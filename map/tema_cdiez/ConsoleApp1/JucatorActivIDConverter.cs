using System.Text.Json;
using System.Text.Json.Serialization;
using ConsoleApp1.domain;

namespace ConsoleApp1;

public class JucatorActivIDConverter : JsonConverter<JucatorActivID>
{
    public JucatorActivIDConverter()
    {
    }

    public override JucatorActivID Read(ref Utf8JsonReader reader, 
        Type typeToConvert, JsonSerializerOptions options)
    {
        var value = reader.GetString();
        var strings = value.Split(":");
        return new JucatorActivID(Guid.Parse(strings[0]), Guid.Parse(strings[1]));
    }
    

    public override void Write(Utf8JsonWriter writer, JucatorActivID value,
        JsonSerializerOptions options)
    {
        writer.WriteStringValue($"{value.idJucator.ToString()}:{value.idMeci.ToString()}");
    }

    public override JucatorActivID ReadAsPropertyName(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
    {
        var value = reader.GetString();
        var strings = value.Split(":");
        return new JucatorActivID(Guid.Parse(strings[0]), Guid.Parse(strings[1]));
    }

    public override void WriteAsPropertyName(Utf8JsonWriter writer, JucatorActivID value, JsonSerializerOptions options)
    {
        writer.WritePropertyName($"{value.idJucator.ToString()}:{value.idMeci.ToString()}");
    }
}