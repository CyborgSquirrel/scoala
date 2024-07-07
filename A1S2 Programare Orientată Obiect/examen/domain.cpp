#include "./domain.hpp"

#include <cassert>

Gen genFromString(const std::string &str) {
	if (str == "pop") {
		return Gen::POP;
	} else if (str == "rock") {
		return Gen::ROCK;
	} else if (str == "folk") {
		return Gen::FOLK;
	} else if (str == "disco") {
		return Gen::DISCO;
	}
	return Gen::POP;
}

std::string stringFromGen(Gen gen) {
	if (gen == Gen::POP) {
		return "pop";
	} else if (gen == Gen::ROCK) {
		return "rock";
	} else if (gen == Gen::FOLK) {
		return "folk";
	} else if (gen == Gen::DISCO) {
		return "disco";
	}
	return "pop";
}


Melodie::Melodie(
	int id,
	const std::string &titlu,
	const std::string &artist,
	Gen gen
) : m_id(id), m_titlu(titlu), m_artist(artist), m_gen(gen)
{ }

int Melodie::getId() const { return m_id; }
const std::string &Melodie::getTitlu() const { return m_titlu; }
const std::string &Melodie::getArtist() const { return m_artist; }
Gen Melodie::getGen() const { return m_gen; }

void Melodie::setTitlu(const std::string &titlu) { m_titlu = titlu; }
void Melodie::setArtist(const std::string &artist) { m_artist = artist; }
void Melodie::setGen(Gen gen) { m_gen = gen; }

bool Melodie::operator==(const Melodie &other) const {
	return m_id == other.m_id
		&& m_titlu == other.m_titlu
		&& m_artist == other.m_artist
		&& m_gen == other.m_gen;
}

void testDomain() {
	Melodie melodie { 0, "melodie frumoasa", "nicu", Gen::POP };
	
	assert(melodie.getId() == 0);
	assert(melodie.getTitlu() == "melodie frumoasa");
	assert(melodie.getArtist() == "nicu");
	assert(melodie.getGen() == Gen::POP);
	
	melodie.setTitlu("melodie urata");
	melodie.setArtist("inamicu");
	melodie.setGen(Gen::ROCK);
	
	assert(melodie.getTitlu() == "melodie urata");
	assert(melodie.getArtist() == "inamicu");
	assert(melodie.getGen() == Gen::ROCK);
	
	Melodie melodie2 { 0, "melodie urata", "inamicu", Gen::ROCK };
	assert(melodie == melodie2);
	
	assert(genFromString("pop") == Gen::POP);
	assert(genFromString("rock") == Gen::ROCK);
	assert(genFromString("folk") == Gen::FOLK);
	assert(genFromString("disco") == Gen::DISCO);
	
	assert(stringFromGen(Gen::POP) == "pop");
	assert(stringFromGen(Gen::ROCK) == "rock");
	assert(stringFromGen(Gen::FOLK) == "folk");
	assert(stringFromGen(Gen::DISCO) == "disco");
}
