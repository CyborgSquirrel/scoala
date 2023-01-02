using ConsoleApp1.domain;

namespace ConsoleApp1.repo;

public interface IRepo<ID, E>
{
    void Store(E e);
    void Update(E e);
    E Find(ID id);
    void Erase(ID id);
    E[] GetAll();
}