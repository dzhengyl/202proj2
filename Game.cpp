#include "Game.h"
using namespace std;

Game::Game() //constructor
{
	GameTitle(); //game title
	//load in materials from file
	LoadMaterials();
	cout << PROJ2_SIZE << " materials loaded." << endl;

	//ask for ship name
	string userinput; //instantiates the string userinput
	cout << "What is the name of your ship? " << endl; //gets the name of the ship
	getline(cin, userinput);
	m_myShip.SetName(userinput); //sets the name to the userinput
	for (int i = 0; i < PROJ2_SIZE; i++) 
	{
		m_myShip.AddMaterial(m_materials[i]);
	}

}
//displays the the materials and quantity
void Game::DisplayMaterials() 
{
	for (int i = 0; i < PROJ2_SIZE; i++) {
		cout << i + 1 << "." << m_myShip.GetMaterial(i).m_name << " " << m_myShip.GetMaterial(i).m_quantity << endl;
	}
}
void Game::LoadMaterials() 
{
	//open the file 
	ifstream myfile("proj2_data.txt");
	if (myfile.is_open()) {
		for (int i = 0; i < PROJ2_SIZE; i++)
		{
			//creates name,type,material,material2
			string name;
			string type;
			string material1;
			string material2;
			getline(myfile, name, ',');
			getline(myfile, type, ',');
			getline(myfile, material1, ',');
			getline(myfile, material2, '\n');
			m_materials[i] = Material(name, type, material1, material2, 0);
			//loads the materials
		}
	}
	else
	{
		cout << "file did not open" << endl;
	}
	myfile.close(); //closes file
}
void Game::StartGame() {
	
	//gets the userinput in this function
	int userinput;
	do {
		userinput = MainMenu();
		if (userinput == DISPLAY){
			DisplayMaterials();
		}
		else if (userinput == SEARCH)
		{
			SearchMaterials();
		}
		else if (userinput == COMBINE)
		{
			CombineMaterials();
			
		}
		else if (userinput == CALC)
		{
			CalcScore();
		}
		
	} while (userinput != QUIT and m_myShip.GetRank() != 'S');
	if (m_myShip.GetRank() == 'S') {
		cout << "You have reached Rank S and won the game!" << endl;
	}
	
}
void Game::SearchMaterials() 
{	
	//generates random number thats raw material
	int randnum = rand() % RAWMATERIAL;
	cout << m_materials[randnum].m_name << " found!" << endl;
	m_myShip.IncrementQuantity(m_myShip.GetMaterial(randnum));
}
int Game::MainMenu()
{
	//menu option
	int options;
	do {
		cin.clear();
		cout << "What would you like to do? " << endl;
		cout << "1. Display your Ship\'s Materials" << endl;
		cout << "2. Search for Raw Materials" << endl;
		cout << "3. Attempt to Merge Materials" << endl;
		cout << "4. See Score" << endl;
		cout << "5. Quit" << endl;
		cin >> options;
		cin.ignore(256, '\n');
		
	} while (options < 1 || options > QUIT);
	return options;
}
void Game::CombineMaterials()
{
	
	//initizializes the variables
	int material1num, material2num, newmaterialnum;
	string material1, material2, newmaterial;
	bool check;
	//ask for material 1
	RequestMaterial(material1num);
	//ask for material 2
	RequestMaterial(material2num);
	material1 = m_materials[material1num - 1].m_name;
	material2 = m_materials[material2num - 1].m_name;
	
	newmaterialnum = SearchRecipes(material1, material2);
	if (newmaterialnum == NEGATIVE) {
		cout << "Nothing happened when you tried to combine " << material1 << " and  " << material2 << endl;
	}
	else
	{
		//gets the new material after combining material 1 and material 2
		newmaterial = m_materials[newmaterialnum].m_name;
		check = m_myShip.CheckQuantity(m_materials[material1num - 1], m_materials[material2num - 1]);
		if (check == false)
		{
			cout << "you don't have enough " << material1 << " or " << material2 << " to attempt that merge." << endl;
		}
		else
		{
			cout << material1 << " combined with " << material2 << " to make " << newmaterial << endl;
			cout << "You have built " << newmaterial << " for your ship." << endl;
			m_myShip.IncrementQuantity(m_materials[newmaterialnum]);
			m_myShip.DecrementQuantity(m_materials[material1num - 1]);
			m_myShip.DecrementQuantity(m_materials[material2num - 1]);
		}
	}
}
//attempts to merge the materials
void Game::RequestMaterial(int &choice) {
	int material;
	do {
		
		cin.clear();
		cout << "Which materials would you like to merge? " << endl;
		cout << "to list known materials enter -1" << endl;
		cin >> material;
		cin.ignore(256, '\n');
		if (material == NEGATIVE) {
			DisplayMaterials();
		}
	} while (material < 1 || material > PROJ2_SIZE);
	choice = material;
}
//searches for materials and see if you can merge
int Game::SearchRecipes(string material1, string material2)
{
	for (int i = 0; i < PROJ2_SIZE; i++) {
		//searches all combinations of the recipe
		if (material1 == m_materials[i].m_material1 || material1 == m_materials[i].m_material2)
		{
			if (material2 == m_materials[i].m_material1 || material2 == m_materials[i].m_material2)
			{
				return i;
			}
		}
	}
	return -1;
}
void Game::CalcScore() {
	//calculates the score. prints THE SHIP name, and rank
	cout << "***The Ship***" << endl;
	cout << "The Great Ship " << m_myShip.GetName() << endl;
	cout << "The Ship Rank: " << m_myShip.GetRank() << endl;
}