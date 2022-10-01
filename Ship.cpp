#include "Ship.h"
#include "Game.h"

using namespace std;

Ship::Ship()
{
	m_shipName = "";
	m_numMaterials = PROJ2_SIZE;
	// initialize all materials to a dummy
	for (int i = 0; i < PROJ2_SIZE; i++) {
		m_myMaterials[i] = Material("0", "0", "0", "0", 0);
	}
}
Ship::Ship(string name)
{
	m_shipName = name;
	m_numMaterials = PROJ2_SIZE;
	for (int i = 0; i < PROJ2_SIZE; i++) {
		m_myMaterials[i] = Material("0", "0", "0", "0", 0);
	}
}
string Ship::GetName() //the getter
{
	return m_shipName;
}
void Ship::SetName(string name) //the setter
{
	m_shipName = name; //sets the name
}
void Ship::AddMaterial(Material item) {
	int count = 0;
	bool stop = false;
	// find the first dummy material index
	while (not stop and count < PROJ2_SIZE) {
		// if dummy, then add item into that position
		if (m_myMaterials[count].m_name == "0") {
			m_myMaterials[count] = item;
			stop = true;
		}
		count++;
	}
}
Material Ship::GetMaterial(int a) {
	return m_myMaterials[a];
}
void Ship::IncrementQuantity(Material item) {
	//loops through to find the material then add to quantity
	for (int i = 0; i < PROJ2_SIZE; i++) {
		if (m_myMaterials[i].m_name == item.m_name) {
			m_myMaterials[i].m_quantity++;
		}
	}
}
bool Ship::DecrementQuantity(Material item) {
	//loops to look for the material to decrememnt the quantity
	for (int i = 0; i < PROJ2_SIZE; i++) {
		if (m_myMaterials[i].m_name == item.m_name) {
			if (m_myMaterials[i].m_quantity < 1)
			{
				return false;
			}
			else
			{
				m_myMaterials[i].m_quantity = m_myMaterials[i].m_quantity - 1;
				return true;
			}
		}
	}
	return false;
}
char Ship::GetRank() {
	//increment rank and checks to see if rank is ranked up
	IncRank();
	//returns the rank of the ship
	return m_shipRank;
}
bool Ship::CheckQuantity(Material material1, Material material2) {
	//checks the quantity and returns a boolean to make sure we have enough to merge
	int material1num, material2num, material3num;
	material1num = CheckMaterial(material1);
	material2num = CheckMaterial(material2);
	for (int i = 0; i < PROJ2_SIZE; i++) {
		//or statment to and nested loop to check if material1 nad material2 are in either order
		if (m_myMaterials[i].m_material1 == material1.m_name || m_myMaterials[i].m_material1 == material2.m_name)
		{
			if (m_myMaterials[i].m_material2 == material1.m_name || m_myMaterials[i].m_material2 == material2.m_name)
			{
				//gets new material index
				material3num = i;
			}
		}
	}
	if (material1num == -1 || material2num == -1) {
		return false;
	}
	else
	{
		if (material1.m_name == material2.m_name) {
			//makes sure we have enough if we are combining the same material
			if (m_myMaterials[material1num].m_quantity < AVAILIBLEQUANTITY)
			{
				return false;
			}
			else
			{
				return true;
			}
			}
			else
			{
				if (m_myMaterials[material3num].m_type == "unique" && m_myMaterials[material3num].m_quantity > 1)
				{
					//checks for multiple of same unique item
					cout << "you already have 1 of this unique item" << endl;
					return false;
				}
				else
				{
					//returns false if we dont have enough quantity
					if (m_myMaterials[material1num].m_quantity < 1 || m_myMaterials[material2num].m_quantity < 1) {
						return false;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}
int Ship::CheckMaterial(Material material) {
	for (int i = 0; i < PROJ2_SIZE; i++)
	{
		//checks if material exists
		if (m_myMaterials[i].m_name == material.m_name)
		{
			return i;
		}
	}
	return -1;
}
void Ship::IncRank() {
	//loops and checks for all unique items and increments rank if needed
	int count = 0;
	for (int i = 0; i < PROJ2_SIZE; i++) {
		if (m_myMaterials[i].m_type == UNIQUE && m_myMaterials[i].m_quantity > 0){
			count++;
		}
	}
	if (count == D) {
		m_shipRank = 'D';
	}
	else if (count == C) {
		m_shipRank = 'C';
	}
	else if (count == B) {
		m_shipRank = 'B';
	}
	else if (count == A){
		m_shipRank = 'A';
	}
	else {
		m_shipRank = 'S';
	}

}