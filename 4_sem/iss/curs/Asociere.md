Relații între [[Clasă|clase]] care reprezintă mulțimi de [[Legătură|legături]].

Proprietăți:
- nume (`detine`, etc.)
- roluri (`+proprietar`, `+ecuson`, etc.)
- [[Multiplicitate|multiplicități]] (`1`, `0..1`, `0..*`, `1..*`, `*`, etc.)

Direcționalitate:
- unidirecțională
- bidirecțională

>[!note]
>Dacă relația este bidirecțională, atunci ambele capete trebuie sincronizate.

Fiecare capăt poate fie etichetat cu un nume de rol.

Fiecare capăt poate fi etichetat cu o mulțime de întregi, care reprezintă multiplicitatea:
- 1
- 0..1
- 1..\*
- 0..\*
- \*

![[Pasted image 20230604180958.png]]

![[Pasted image 20230604181219.png]]

Li se pot atașa atribute și operații, la fel ca la [[Clasă|clase]].

![[Pasted image 20230604181417.png]]

![[Pasted image 20230604181423.png]]

Calificarea: Asociezi o cheie unui atribut.

Before calificare:
![[Pasted image 20230604182040.png]]

After calificare: (mind_blown.gif)
![[Pasted image 20230604182105.png]]

direcția îți spune cine e copilul

# Tipuri

## Unidirecționale one-to-one

![[Pasted image 20230605200640.png]]

```java
public class Advertiser {
	private Account account;
	
	public Advertiser()
	{
		account = new Account();
	}
	
	public Account getAccount()
	{
		return account;
	}
}
```

## Bidirecționale one-to-one

![[Pasted image 20230605201010.png]]

```java
public class Advertiser {
	private Account account;
	
	public Advertiser()
	{
		account = new Account(this);
	}
	
	public Account getAccount()
	{
		return account;
	}
}
```

```java
public class Account {
	private Advertiser owner;
	
	public Account(Advertiser owner)
	{
		this.owner = owner;
	}
	
	public Advertiser getOwner()
	{
		return owner;
	}
}
```

# Bidirecționale one-to-many

![[Pasted image 20230605201146.png]]

```java
public class Advertiser {
	private Set<Account> accounts;
	
	public Advertiser()
	{
		accounts = new HashSet();
	}
	
	public void addAccount(Account account)
	{
		if (!accounts.contains(account))
		{
			accounts.add(account);
			account.internalSetOwner(this);
		}
	}
	
	public void removeAccount(Account account)
	{
		if (accounts.contains(account))
		{
			accounts.remove(account);
			accounts.internalSetOwner(null);
		}
	}
	
	public void internalAddAccount(Account account)
	{
		if (!accounts.contains(account))
		{
			accounts.add(account);
		}
	}
	
	public void internalRemoveAccount(Account account)
	{
		if (accounts.contains(account))
		{
			accounts.remove(account);
		}
	}
	
	public Set<Account> getAccounts()
	{
		return Collections.unmodifiableSet(accounts);
	}
}
```

```java
public class Account {
	private Advertiser owner;
	
	public void setOwner(Advertiser owner)
	{
		Advertiser oldOwner = this.owner;
		Advertiser newOwner = owner;
		if (oldOwner != null)
		{
			oldOwner.internalRemoveAccount(this);
		}
		if (newOwner != null)
		{
			newOwner.internalAddAccount(this);
		}
		this.owner = newOwner;
	}
	
	void internalSetOwner(Advertiser owner)
	{
		this.owner = owner;
	}
	
	public Advertiser getOwner()
	{
		return owner;
	}
}
```

## Bidirecționale many-to-many

![[Pasted image 20230605202254.png]]

```java
public class Player {
	private Set<Tournament> tournaments;
	
	public Player()
	{
		tournaments = new HashSet();
	}
	
	public void addTournament(Tournament tournament)
	{
		if (!tournaments.contains(tournament))
		{
			tournaments.add(tournament);
			tournament.internalAddPlayer(this);
		}
	}
	
	public void removeTournament(Tournament tournament)
	{
		if (tournaments.contains(tournament))
		{
			tournaments.remove(tournament);
			tournament.internalRemovePlayer(this);
		}
	}
	
	void internalAddTournament(Tournament tournament)
	{
		if (!tournaments.contains(tournament))
		{
			tournaments.add(tournament);
		}
	}
	
	void internalRemoveTournament(Tournament tournament)
	{
		if (tournaments.contains(tournament))
		{
			tournaments.remove(tournament);
		}
	}
	
	public Set<Tournament> getTournaments()
	{
		return Collections.unmodifiableSet(tournaments);
	}
}
```

```java
public class Tournament {
	private Set<Player> players;
	
	public Tournament()
	{
		players = new HashSet();
	}
	
	public void addPlayer(Player player)
	{
		if (!players.contains(player))
		{
			players.add(player);
			player.internalAddTournament(this);
		}
	}
	
	public void removePlayer(Player player)
	{
		if (players.contains(player))
		{
			players.remove(player);
			player.internalRemoveTournament(this);
		}
	}
	
	void internalAddPlayer(Player player)
	{
		if (!players.contains(player))
		{
			players.add(player);
		}
	}
	
	void internalRemovePlayer(Player player)
	{
		if (players.contains(player))
		{
			players.remove(player);
		}
	}
	
	public Set<Player> getPlayers()
	{
		return Collections.unmodifiableSet(players);
	}
}
```

## Calificate

![[Pasted image 20230605202510.png]]

```java
public class League {
	private Map<String, Player> players;
	
	public League()
	{
		players = new HashMap();
	}
	
	public void addPlayer(String nickName, Player player)
	{
		if (!players.containsKey(nickName))
		{
			players.put(nickName, player);
			player.internalAddLeague(this);
		}
	}
	
	public Player getPlayer(String nickName)
	{
		return players.get(nickName);
	}
	
	void internalAddPlayer(String nickName, Player player)
	{
		if (!players.containsKey(nickName)) {
			players.put(nickName, player);
		}
	}
}
```

```java
public class Player {
	private Set<League> leagues;
	
	public Player()
	{
		leagues = new HashSet();
	}
	
	public void addLeague(League league, String nickName)
	{
		if (league.getPlayer(nickName) == null)
		{
			leagues.add(league);
			league.internalAddPlayer(nickName, this);
		}
	}
	
	void internalAddLeague(League league)
	{
		leagues.add(league);
	}
}
```