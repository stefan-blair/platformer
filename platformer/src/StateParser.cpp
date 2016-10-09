#include "StateParser.h"
#include "Melee_Weapon_Types.h"
#include "FinishBlock.h"

StateParser::StateParser()
{
}


StateParser::~StateParser()
{
}
int StateParser::_currentIndex = 0;
bool StateParser::_end = false;

void StateParser::loadStateObjects(std::string fileName, Player* player, std::vector<SDLGameObject*>* objects){
	std::ifstream file("assets/Objects/"+fileName+".txt");

	std::string str;

	std::string type, textureFile;
	int x, y, width, height;
	SDLGameObject_Values attributes;

	while (std::getline(file, str))
	{
		if (getNextWord(&str) == "new"){
			type = getNextWord(&str);
			bool running = true;
			std::string currentWord;
			_end = false;
			_currentIndex = 0;
			while (running){
				std::getline(file, str);
				currentWord = getNextWord(&str);
				if (currentWord == "int"){
					currentWord = getNextWord(&str);
					int* variable = 0;
					if (currentWord == "x")
						variable = &x;
					else if (currentWord == "y")
						variable = &y;
					else if (currentWord == "width")
						variable = &width;
					else if (currentWord == "height")
						variable = &height;
					else if (currentWord == "money")
						variable = &attributes.money;
					else if (currentWord == "skill_points")
						variable = &attributes.skill_points;
					else if (currentWord == "walkSpeed")
						variable = &attributes.walkSpeed;
					else if (currentWord == "runSpeed")
						variable = &attributes.runSpeed;
					else if (currentWord == "weight")
						variable = &attributes.weight;
					else if (currentWord == "jumpHeight")
						variable = &attributes.jumpHeight;
					else if (currentWord == "health")
						variable = &attributes.health;
					else if (currentWord == "range")
						variable = &attributes.range;
					*variable = stoi(getNextWord(&str));
				}
				
				else if (currentWord == "string"){
					currentWord = getNextWord(&str);
					if (currentWord == "file"){
						textureFile = getNextWord(&str);
					}
				}
				else if (currentWord == "end"){
					running = false;

					objects->push_back(GameObjectFactory::create(type));
					objects->back()->SDLGameObject::init(new LoaderParams(x, y, width, height, TextureManager::Instance()->load(textureFile, Game::Instance()->getRenderer())));
					objects->back()->SDLGameObject::initAttr(attributes);
					objects->back()->setPlayerLocation(player->getPosition());
				}
				_end = false;
				_currentIndex = 0;
			}
		}
	}

}

void StateParser::loadStateTiles(std::string fileName,  Tiles* tiles){
	std::ifstream mapFile("assets/Maps/" + fileName + ".txt");
	std::string str;
	std::getline(mapFile, str);

	tiles->init(new LoaderParams(stoi(getNextWord(&str)), stoi(getNextWord(&str)), 31, 31, TextureManager::Instance()->load("assets/Textures/tiles.jpg", Game::Instance()->getRenderer())));
	_end = false;
	_currentIndex = 0;
	int y = 0;
	int x;

	int frame = 0;
	tile* current_tile;
	while (std::getline(mapFile, str))
	{
		x = -1;
		std::string current_word = getNextWord(&str);
		while (!_end){
			++x;
			if (current_word[0] == '~'){
				tiles->addTile(0);
				goto END;
			}
			current_tile = new tile;
			tiles->addTile(current_tile);
			current_tile->_row = current_word[0] - 48;
			current_tile->_frame = current_word[1] - 48;
		END:
			current_word = getNextWord(&str);
		}
		_end = false;
		_currentIndex = 0;
		++y;
	}

}

void StateParser::loadStatePlayerAttr(Player* player){
	//factory->registerType("enemy", new EnemyCreator());

	std::ifstream file("assets/Save_Data/Saved_Data.txt");
	std::string str;

	SDLGameObject_Values player_values;

	Melee_Weapon* current_melee_weapon;
	Projectile_Weapon* current_projectile_weapon;

	_currentIndex = 0;
	while (std::getline(file, str))
	{
		_currentIndex = 0;
		std::string baseWord = getNextWord(&str);
		if (baseWord == "attr"){
			bool running = true;
			std::string currentWord;
			_end = false;
			_currentIndex = 0;
			while (running){
				std::getline(file, str);
				currentWord = getNextWord(&str);
				int* variable = 0;
				if (currentWord == "end"){
					running = false;
					player->initAttr(player_values);
					continue;
				}
				else if (currentWord == "money")
					variable = &player_values.money;
				else if (currentWord == "skill_points")
					variable = &player_values.skill_points;
				else if (currentWord == "walkSpeed")
					variable = &player_values.walkSpeed;
				else if (currentWord == "runSpeed")
					variable = &player_values.runSpeed;
				else if (currentWord == "weight")
					variable = &player_values.weight;
				else if (currentWord == "jumpHeight")
					variable = &player_values.jumpHeight;
				else if (currentWord == "health")
					variable = &player_values.health;
				*variable = stoi(getNextWord(&str));
			
				_end = false;
				_currentIndex = 0;
			}
		}
		if (baseWord == "projectile_weapon"){
			bool running = true;
			std::string currentWord;
			_end = false;
			_currentIndex = 0;

			int position = 0;
			current_projectile_weapon = new Projectile_Weapon(player);
			Projectile_Weapon_Values projectile_values;
			std::string projectile_type;
			while (running){
				_end = false;
				_currentIndex = 0;
				std::getline(file, str);
				currentWord = getNextWord(&str);
				int* variable = 0;
				if (currentWord == "end"){
					running = false;
					current_projectile_weapon->init(projectile_values);
					player->equip(position, current_projectile_weapon, 0);
					continue;
				}
				else if (currentWord == "type"){
					projectile_type = getNextWord(&str);
					readProjectileValues(projectile_type, projectile_values);
					continue;
				}
				else if (currentWord == "position")
					variable = &position;
				else if (currentWord == "price")
					variable = &projectile_values.price;
				else if (currentWord == "id")
					variable = &projectile_values.id;
				else if (currentWord == "range")
					variable = &projectile_values.range;
				else if (currentWord == "damage")
					variable = &projectile_values.damage;
				else if (currentWord == "bulletSpeed")
					variable = &projectile_values.bulletSpeed;
				else if (currentWord == "ammunition")
					variable = &projectile_values.ammunition;
				else if (currentWord == "rechargeTime")
					variable = &projectile_values.rechargeTime;
				*variable += stoi(getNextWord(&str));
			}
		}
		if (baseWord == "melee_weapon"){
			bool running = true;
			std::string currentWord;
			_end = false;
			_currentIndex = 0;

			int position = 0;
			current_melee_weapon = new Melee_Weapon(player);
			Melee_Weapon_Values melee_values;
			std::string melee_type;
			while (running){
				_end = false;
				_currentIndex = 0;
				std::getline(file, str);
				currentWord = getNextWord(&str);
				int* variable = 0;
				if (currentWord == "end"){
					running = false;
					current_melee_weapon->init(melee_values);
					player->equip(position, 0, current_melee_weapon);
					continue;
				}
				else if (currentWord == "type"){
					melee_type = getNextWord(&str);
					readMeleeValues(melee_type, melee_values);
					continue;
				}
				else if (currentWord == "position"){
					position = stoi(getNextWord(&str));
					continue;
				}
				else if (currentWord == "range")
					variable = &melee_values.range;
				else if (currentWord == "damage")
					variable = &melee_values.damage;
				else if (currentWord == "price")
					variable = &melee_values.price;
				else if (currentWord == "id")
					variable = &melee_values.id;
				else if (currentWord == "rechargeTime")
					variable = &melee_values.rechargeTime;
				*variable += stoi(getNextWord(&str));
				
			}
		}
		_currentIndex = 0;
	}

	/*current_melee_weapon = new Melee_Weapon(player);
	current_melee_weapon->init(Melee_Weapon_Factory::getMeleeValues("SWORD"));
	player->equip(0, 0, current_melee_weapon);*/
}

void StateParser::loadStatePlayer(std::string level, Player* player){
	//GameObjectFactory* factory = new GameObjectFactory();
	//factory->registerType("player", new PlayorCreator());

	std::ifstream file("assets/Objects/"+level+"_Player"+".txt");
	std::string str;

	std::string textureFile;
	int x, y, width, height;

	_currentIndex = 0;
	while (std::getline(file, str))
	{
		_currentIndex = 0;
		std::string baseWord = getNextWord(&str);
		if (baseWord == "player"){
			bool running = true;
			std::string currentWord;
			_end = false;
			_currentIndex = 0;
			while (running){
				std::getline(file, str);
				currentWord = getNextWord(&str);
				if (currentWord == "int"){
					currentWord = getNextWord(&str);
					int* variable = 0;
					if (currentWord == "x")
						variable = &x;
					else if (currentWord == "y")
						variable = &y;
					else if (currentWord == "width")
						variable = &width;
					else if (currentWord == "height")
						variable = &height;
					*variable = stoi(getNextWord(&str));
				}

				else if (currentWord == "string"){
					currentWord = getNextWord(&str);
					if (currentWord == "file"){
						textureFile = getNextWord(&str);
					}
				}
				else if (currentWord == "end"){
					running = false;
					player->SDLGameObject::init(new LoaderParams(x, y, width, height, TextureManager::Instance()->load(textureFile, Game::Instance()->getRenderer())));
				}
				_end = false;
				_currentIndex = 0;
			}
		}
		

		_currentIndex = 0;
	}
}

void StateParser::getCurrentLevel(std::string& level){

	std::ifstream file("assets/Save_Data/Saved_Level.txt");

	std::string str;

	std::getline(file, str);
	level = str;
}

void StateParser::readMeleeValues(std::string& type, Melee_Weapon_Values& values){
	std::ifstream file("assets/WeaponSheets/"+type+".txt");
	std::string str;

	std::string currentword;
	_currentIndex = 0;
	_end = false;
	while (std::getline(file, str))
	{
		_currentIndex = 0;
		_end = false;
		currentword = getNextWord(&str);
		if (currentword == "damage"){
			values.damage = stoi(getNextWord(&str));
		}
		else if (currentword == "id"){
			values.id = stoi(getNextWord(&str));
		}
		else if (currentword == "price"){
			values.price = stoi(getNextWord(&str));
		}
		else if (currentword == "range"){
			values.range = stoi(getNextWord(&str));
		}
		else if (currentword == "rechargeTime"){
			values.rechargeTime = stoi(getNextWord(&str));
		}
		else if (currentword == "type"){
			values.type = getNextWord(&str);
		}
	}
}
void StateParser::readProjectileValues(std::string& type, Projectile_Weapon_Values& values){
	std::ifstream file("assets/WeaponSheets/" + type + ".txt");
	std::string str;

	std::string currentword;
	_currentIndex = 0;
	_end = false;
	while (std::getline(file, str))
	{
		_currentIndex = 0;
		_end = false;
		currentword = getNextWord(&str);
		if (currentword == "damage"){
			values.damage = stoi(getNextWord(&str));
		}
		else if (currentword == "id"){
			values.id = stoi(getNextWord(&str));
		}
		else if (currentword == "price"){
			values.price = stoi(getNextWord(&str));
		}
		else if (currentword == "range"){
			values.range = stoi(getNextWord(&str));
		}
		else if (currentword == "rechargeTime"){
			values.rechargeTime = stoi(getNextWord(&str));
		}
		else if (currentword == "ammunition"){
			values.ammunition = stoi(getNextWord(&str));
		}
		else if (currentword == "bulletSpeed"){
			values.bulletSpeed = stoi(getNextWord(&str));
		}
		else if (currentword == "type"){
			values.type = getNextWord(&str);
		}

		//ammunition 0
//		bulletSpeed 10
	}
}

std::string StateParser::getNextWord(std::string* line){
	if (_currentIndex == line->length())
		_end = true;
	int beginningIndex = _currentIndex;
	for (_currentIndex; _currentIndex < line->length(); ++_currentIndex){
		if ((*line)[_currentIndex] == ' '){
			++_currentIndex;
			return line->substr(beginningIndex, _currentIndex - beginningIndex-1);
		}
	}
	return line->substr(beginningIndex, _currentIndex - beginningIndex);
}