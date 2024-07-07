// Online C# Editor for free
// Write, Edit and Run your C# code using C# Online Compiler

using System;

abstract class RailCar {
    private string name;
    private RailCar next;

    public RailCar(string name) {
        if (name.Length < 2) {
            throw new ArgumentException("name must have >=2 chars");
        }
        this.name = name;
    }
    
    public abstract bool isProfitable();
    public abstract string toString();
    public abstract RailCar clone();
    
    public RailCar getNext() {
        return next;
    }
    public void setNext(RailCar next) {
        this.next = next;
    }
    public string getName() {
        return name;
    }
}

class Locomotive {
    private RailCar first;
    
    public Locomotive() {
        
    }
    
    public RailCar getFirstRailCar() {
        return first;
    }
    
    public void setFirstRailCar(RailCar first) {
        this.first = first;
    }
    
    public void attachRailCar(RailCar railCar) {
        RailCar curr = first;
        RailCar prev = null;
        while (
            curr != null
            && String.Compare(railCar.toString(), curr.toString(), StringComparison.Ordinal) > 0
        ) {
            prev = curr;
            curr = curr.getNext();
        }
        
        if (prev != null) {
            prev.setNext(railCar);
        } else {
            first = railCar;
        }
        railCar.setNext(curr);
    }
}

class PassengerCar : RailCar {
    private int capacity;
    
    public PassengerCar(string name, int capacity) : base(name) {
        this.capacity = capacity;
    }
    
    public override bool isProfitable() {
        return capacity > 40;
    }
    
    public override string toString() {
        return getName() + capacity.ToString();
    }
    
    public override RailCar clone() {
        return new PassengerCar(getName(), capacity);
    }
}

class RestaurantCar : RailCar {
    private int numberOfTables;
    
    public RestaurantCar(string name, int numberOfTables) : base(name) {
        this.numberOfTables = numberOfTables;
    }
    
    public override bool isProfitable() {
        return numberOfTables >= 20;
    }
    
    public override string toString() {
        return getName() + numberOfTables.ToString();
    }
    
    public override RailCar clone() {
        return new RestaurantCar(getName(), numberOfTables);
    }
}

public class HelloWorld
{
    static void locoCostCutting(Locomotive l) {
        RailCar curr = l.getFirstRailCar();
        RailCar prev = null;
        while (curr != null) {
            if (!curr.isProfitable()) {
                if (prev != null) {
                    prev.setNext(curr.getNext());
                } else {
                    l.setFirstRailCar(curr.getNext());
                }
                RailCar next = curr.getNext();
                curr.setNext(null);
                curr = next;
            } else {
                prev = curr;
                curr = curr.getNext();
            }
        }
    }
    
    static Locomotive locoInsaneoMode(Locomotive l) {
        Locomotive lp = new Locomotive();
        
        RailCar clone = null;
        
        RailCar curr = l.getFirstRailCar();
        while (curr != null) {
            RailCar newClone = curr.clone();
            newClone.setNext(clone);
            clone = newClone;
            
            curr = curr.getNext();
        }
        
        lp.setFirstRailCar(clone);
        return lp;
    }
    
    public static void Main(string[] args)
    {
        Locomotive l = new Locomotive();
        
        l.attachRailCar(new PassengerCar("aa", 50));
        l.attachRailCar(new PassengerCar("bb", 32));
        l.attachRailCar(new PassengerCar("dd", 40));
        
        l.attachRailCar(new RestaurantCar("cc", 25));
        l.attachRailCar(new RestaurantCar("ee", 20));
        
        locoCostCutting(l);
        Locomotive lp = locoInsaneoMode(l);
        
        RailCar curr = lp.getFirstRailCar();
        while (curr != null) {
            Console.WriteLine(curr.toString());
            
            curr = curr.getNext();
        }
    }
}
