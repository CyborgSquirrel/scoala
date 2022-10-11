# Biblioteca

- Carte
- Autor
- Editura
- Imprumut
- Abonament
- Gen

## CarteDate
* id
- autor_id (-> Autor.id)
- editura_id (-> Editura.id)
- titlu
- data publicare

## Carte
* id
- carte_date_id (-> CarteDate.id)

## Autor
* id
- nume

## Editura
* id
- nume

## Abonament
* id
- detinator_nume

## Imprumut
* id
- carte_id (-> Carte.id)
- abonament_id (-> Abonament.id)
- data inceput
- data sfarsit

## Gen
* id
- nume

## CarteGen
* carte_date_id (-> CarteDate.id)
* gen_id (-> Gen.id)

## Raft
* id
- latime
- inaltime

## LocRaft
* raft_id (-> Raft.id)
* linie
* coloana
- carte_id (-> Carte.id)
