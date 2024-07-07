#include "./repo.hpp"

#include <fstream>
#include <cassert>

RepoException::RepoException(const std::string &msg) : m_msg(msg) { }

const std::string &RepoException::getMsg() const {
	return m_msg;
}

void RepoMelodie::readAllFromFile() {
	std::ifstream fin(m_filePath);
	std::string line;
	while (std::getline(fin, line)) {
		std::vector<std::string> fields;
		std::string field = "";
		for (const auto c : line) {
			if (c == ',') {
				fields.push_back(field);
				field.clear();
			} else {
				field += c;
			}
		}
		fields.push_back(field);
		field.clear();
		
		if (fields.size() >= 4) {
			int id = std::stoi(fields[0]);
			std::string titlu = fields[1];
			std::string artist = fields[2];
			Gen gen = genFromString(fields[3]);
			
			Melodie melodie { id, titlu, artist, gen };
			m_melodii.push_back(melodie);
		}
	}
}

void RepoMelodie::writeAllToFile() const {
	std::ofstream fout(m_filePath);
	for (const auto &melodie : m_melodii) {
		fout << melodie.getId() << ","
		     << melodie.getTitlu() << ","
		     << melodie.getArtist() << ","
		     << stringFromGen(melodie.getGen()) << "\n";
	}
}

RepoMelodie::RepoMelodie(const std::string &filePath)
: m_filePath(filePath)
{
	readAllFromFile();
}

int RepoMelodie::getLength() const {
	return m_melodii.size();
}

void RepoMelodie::store(const Melodie &melodie) {
	for (const auto &otherMelodie : m_melodii) {
		if (otherMelodie.getId() == melodie.getId()) {
			throw RepoException { "deja exista o melodie cu id-ul acestei melodii in repo" };
		}
	}
	m_melodii.push_back(melodie);
	writeAllToFile();
}

void RepoMelodie::erase(int id) {
	int index;
	bool found = false;
	for (size_t i = 0; !found && i < m_melodii.size(); ++i) {
		const auto &melodie = m_melodii[i];
		if (melodie.getId() == id) {
			index = i;
			found = true;
		}
	}
	
	if (!found) {
		throw RepoException { "nu exista melodie cu id-ul furnizat in repo" };
	}
	m_melodii.erase(m_melodii.begin() + index);
	writeAllToFile();
}

const std::vector<Melodie> &RepoMelodie::getAll() const {
	return m_melodii;
}

void testRepo() {
	{
		std::ofstream fout { "./melodii_test.txt" };
		fout << "0,melodie frumoasa,nicu,pop\n";
		fout << "1,melodie urata,inamicu,rock\n";
		fout << "2,5bani 100bani,gicu,folk\n";
		fout << "3,meloada,stefan,folk\n";
		fout.close();
	}
	
	RepoMelodie repo { "./melodii_test.txt" };
	assert(repo.getLength() == 4);
	
	std::vector<Melodie> v1 {
		Melodie { 0, "melodie frumoasa", "nicu", Gen::POP },
		Melodie { 1, "melodie urata", "inamicu", Gen::ROCK },
		Melodie { 2, "5bani 100bani", "gicu", Gen::FOLK },
		Melodie { 3, "meloada", "stefan", Gen::FOLK }
	};
	assert(repo.getAll() == v1);
	
	repo.store(Melodie { 4, "stairway to idk", "roacher", Gen::ROCK });
	repo.erase(3);
	
	std::vector<Melodie> v2 {
		Melodie { 0, "melodie frumoasa", "nicu", Gen::POP },
		Melodie { 1, "melodie urata", "inamicu", Gen::ROCK },
		Melodie { 2, "5bani 100bani", "gicu", Gen::FOLK },
		Melodie { 4, "stairway to idk", "roacher", Gen::ROCK }
	};
	assert(repo.getAll() == v2);
}
