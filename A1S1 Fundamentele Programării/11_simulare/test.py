import unittest

from repo import RepoMateriale, \
CodDejaUtilizatException, CodInexistentException, \
MaterialInexistentException
from entity import Material

from srv import SrvMateriale

class TestRepoMateriale(unittest.TestCase):
	def test_store(self):
		repo = RepoMateriale()
		repo.store(Material(1, "Lemn", "m3", 100.3, 5.5))
		with self.assertRaises(CodDejaUtilizatException):
			repo.store(Material(1, "Piatra", "m3", 22.1, 15.25))
	
	def test_find(self):
		repo = RepoMateriale()
		
		material = Material(1, "Lemn", "m3", 100.2, 5.5)
		repo.store(material)
		self.assertEqual(material, repo.find(1))
		
		with self.assertRaises(CodInexistentException):
			repo.find(2)
	
	def test_update(self):
		repo = RepoMateriale()
		
		material = Material(1, "Asbest", "m3", 123.2, 45.5)
		repo.store(material)
		
		material = Material(1, "Lemn", "m3", 100.2, 5.5)
		repo.update(material)
		
		with self.assertRaises(MaterialInexistentException):
			material = Material(2, "Lemn", "m3", 100.2, 5.5)
			repo.update(material)
	
	def test_get_all(self):
		repo = RepoMateriale()
		
		materiale = [Material(1, "Lemn", "m3", 100.2, 5.5), Material(2, "Piatra", "m3", 22.1, 15.25), Material(3, "Asbest", "m3", 431, 434.25)]
		repo.store(materiale[0])
		repo.store(materiale[1])
		repo.store(materiale[2])
		
		self.assertEqual(materiale, repo.get_all())
	
	def test_get_all_dto(self):
		repo = RepoMateriale()
		
		materiale = [Material(1, "Lemn", "m3", 100.2, 5.5), Material(2, "Piatra", "m3", 22.1, 15.25), Material(3, "Asbest", "m3", 431, 434.25)]
		repo.store(materiale[0])
		repo.store(materiale[1])
		repo.store(materiale[2])
		
		material_dtos = repo.get_all_dto()
		self.assertEqual(materiale[0].get_cod(), material_dtos[0].get_cod())
		self.assertEqual(materiale[0].get_denumire(), material_dtos[0].get_denumire())
		self.assertEqual(materiale[0].get_cantitate_pe_stoc(), material_dtos[0].get_cantitate_pe_stoc())
		self.assertEqual(materiale[0].get_pret_unitar(), material_dtos[0].get_pret_unitar())
		
		self.assertEqual(materiale[1].get_cod(), material_dtos[1].get_cod())
		self.assertEqual(materiale[1].get_denumire(), material_dtos[1].get_denumire())
		self.assertEqual(materiale[1].get_cantitate_pe_stoc(), material_dtos[1].get_cantitate_pe_stoc())
		self.assertEqual(materiale[1].get_pret_unitar(), material_dtos[1].get_pret_unitar())
		
		self.assertEqual(materiale[2].get_cod(), material_dtos[2].get_cod())
		self.assertEqual(materiale[2].get_denumire(), material_dtos[2].get_denumire())
		self.assertEqual(materiale[2].get_cantitate_pe_stoc(), material_dtos[2].get_cantitate_pe_stoc())
		self.assertEqual(materiale[2].get_pret_unitar(), material_dtos[2].get_pret_unitar())

unittest.main()