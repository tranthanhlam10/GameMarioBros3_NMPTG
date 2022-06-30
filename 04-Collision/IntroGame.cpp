#include <iostream>
#include <fstream>
#include "debug.h"
#include "IntroGame.h"
#include "IntroGameKey.h"


using namespace std;

IntroGame::IntroGame(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new IntroGameKey(this);

}

#define OBJECT_TYPE_POINTER	21
#define OBJECT_TYPE_GROUND	22
#define OBJECT_TYPE_THREE	23


#define MAX_SCENE_LINE 1024


void IntroGame::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str());

}


void IntroGame::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}


void IntroGame::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}


void IntroGame::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (size_t i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void IntroGame::_ParseSection_OBJECTS(string line)
{
	LPCWSTR path = ToLPCWSTR(line);
	ifstream f; f.open(path);
	if (!f)
		DebugOut(L"\nFailed to open object file!");

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {

		string line(str);
		vector<string> tokens = split(line);

		DebugOut(L"--> %s\n", ToWSTR(line).c_str());

		if (line[0] == '#') continue;
		if (tokens.size() < 3) continue; // skip invalid lines - an object set must have at least id, x, y

		int object_type = atoi(tokens[0].c_str());
		float x = (float)atof(tokens[1].c_str());
		float y = (float)atof(tokens[2].c_str());
		int ani_set_id = atoi(tokens[3].c_str());

		CAnimationSets* animation_sets = CAnimationSets::GetInstance();

		CGameObject* obj = NULL;

		switch (object_type)
		{
		case OBJECT_TYPE_POINTER:
			if (pointer != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			obj = new Pointer(x, y);
			pointer = (Pointer*)obj;

			DebugOut(L"[INFO] pointer object has been created!\n");
			break;
		case OBJECT_TYPE_GROUND:
		{
			obj = new Ground(x, y);
			break;
		}
		case OBJECT_TYPE_THREE:
		{
			obj = new Three(x, y);
			break;
		}

		default:
			DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
			return;
		}

		// General object setup

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	}
	f.close();
}


void IntroGame::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png");

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void IntroGame::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	if (pointer == NULL) return;

	PurgeDeletedObjects();
}


void IntroGame::Render()
{
	CGame* game = CGame::GetInstance();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	
}

/*
*	Clear all objects from this scene
*/
void IntroGame::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

void IntroGame::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	pointer = nullptr;
	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool IntroGame::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void IntroGame::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), IntroGame::IsGameObjectDeleted),
		objects.end());
}