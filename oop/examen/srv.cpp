#include "./srv.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>

int SrvMelodie::getNextId() const {
	const std::vector<Melodie> &melodii = m_repo.getAll();
	int id = 0;
	for (const auto &melodie : melodii) {
		if (melodie.getId() >= id) {
			id = melodie.getId() + 1;
		}
	}
	return id;
}

SrvMelodie::SrvMelodie(RepoMelodie &repo) : m_repo(repo), m_nextCallbackId(0) { }

int SrvMelodie::getLength() const {
	return m_repo.getLength();
}

std::vector<Melodie> SrvMelodie::getMelodiiSortedByAutor() const {
	std::vector<Melodie> melodii = m_repo.getAll();
	std::sort(
		melodii.begin(), melodii.end(),
		[](const Melodie &lhs, const Melodie &rhs)
		{ return lhs.getArtist() < rhs.getArtist(); }
	);
	return melodii;
}

int SrvMelodie::getMelodiiCountWithAutor(const std::string &autor) const {
	const std::vector<Melodie> &melodii = m_repo.getAll();
	int count = 0;
	for (const auto &melodie : melodii) {
		if (melodie.getArtist() == autor) {
			count++;
		}
	}
	return count;
}

int SrvMelodie::getMelodiiCountWithGen(Gen gen) const {
	const std::vector<Melodie> &melodii = m_repo.getAll();
	int count = 0;
	for (const auto &melodie : melodii) {
		if (melodie.getGen() == gen) {
			count++;
		}
	}
	return count;
}

void SrvMelodie::addMelodie(
	std::string titlu,
	std::string artist,
	Gen gen
) {
	m_repo.store(Melodie{
		getNextId(),
		titlu,
		artist,
		gen
	});
	publish();
}

void SrvMelodie::eraseMelodie(
	int id
) {
	m_repo.erase(id);
	publish();
}

void SrvMelodie::publish() {
	for (const auto &idAndCallback : m_callbacks) {
		idAndCallback.second();
	}
}

int SrvMelodie::connect(std::function<void()> callback) {
	int callbackId = m_nextCallbackId;
	m_nextCallbackId++;
	m_callbacks[callbackId] = callback;
	return callbackId;
}

void SrvMelodie::disconnect(int id) {
	m_callbacks.erase(id);
}

void testSrv() {
	{
		std::ofstream fout { "./melodii_test.txt" };
		fout << "0,melodie frumoasa,nicu,pop\n";
		fout << "1,melodie urata,inamicu,rock\n";
		fout << "2,5bani 100bani,gicu,folk\n";
		fout << "3,meloada,stefan,folk\n";
		fout.close();
	}
	
	RepoMelodie repo { "./melodii_test.txt" };
	SrvMelodie srv { repo };
	assert(srv.getLength() == 4);
	
	std::vector<Melodie> v1 {
		Melodie { 2, "5bani 100bani", "gicu", Gen::FOLK },
		Melodie { 1, "melodie urata", "inamicu", Gen::ROCK },
		Melodie { 0, "melodie frumoasa", "nicu", Gen::POP },
		Melodie { 3, "meloada", "stefan", Gen::FOLK }
	};
	assert(srv.getMelodiiSortedByAutor() == v1);
	
	assert(srv.getMelodiiCountWithAutor("gicu") == 1);
	assert(srv.getMelodiiCountWithGen(Gen::FOLK) == 2);
	
	srv.addMelodie("stairway to idk", "roacher", Gen::ROCK);
	srv.eraseMelodie(3);
	
	std::vector<Melodie> v2 {
		Melodie { 2, "5bani 100bani", "gicu", Gen::FOLK },
		Melodie { 1, "melodie urata", "inamicu", Gen::ROCK },
		Melodie { 0, "melodie frumoasa", "nicu", Gen::POP },
		Melodie { 4, "stairway to idk", "roacher", Gen::ROCK }
	};
	assert(srv.getMelodiiSortedByAutor() == v2);
}
