
#include "PlayScence.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	player = NULL;
	
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_DRAWMAP			7

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	13
#define OBJECT_TYPE_PIPE 6
#define OBJECT_TYPE_PLATFORM 7
#define OBJECT_TYPE_QUESTION_BRICK 8
#define OBJECT_TYPE_COLOR_BLOCK 9
#define OBJECT_TYPE_COIN 10
#define OBJECT_TYPE_PLANT 11
#define OBJECT_TYPE_FIRE_PLANT 12
#define OBJECT_TYPE_COIN_BRICK 14
#define OBJECT_TYPE_PORTAL	52
#define MAX_SCENE_LINE 1024


#define SCREEN_HEIGHT 300
#define DISTANCE_FROM_BOTTOM_CAM_TO_TOP_BOARD	90.f

#define GAME_TIME_LIMIT 300

void CPlayScene::_ParseSection_TEXTURES(string line) // load texture từ file txt
{
	vector<string> tokens = split(line); // tách chuỗi

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str());
}

void CPlayScene::_ParseSection_SPRITES(string line)
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

void CPlayScene::_ParseSection_ANIMATIONS(string line)
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

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);	
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line) // hàm dùng để khởi tạo đối tượng 
{
		vector<string> tokens = split(line);
		DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		//if (line[0] == '#') continue;
	if (tokens.size() < 2) return; // skip invalid lines - an object set must have at least id, x, y

		int object_type = atoi(tokens[0].c_str());
		float x = (float)atof(tokens[1].c_str());
		float y = (float)atof(tokens[2].c_str());
		int ani_set_id = (int)atoi(tokens[3].c_str());

		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		CGameObject* obj = NULL;

		switch (object_type)
		{
		case OBJECT_TYPE_MARIO:
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			obj = new CMario(x, y);
			player = (CMario*)obj;

			DebugOut(L"[INFO] Player object created!\n");
			break;	
		case OBJECT_TYPE_GOOMBA: 
		{
			int model = (int)atof(tokens[4].c_str());
			obj = new CGoomba(x, y, model); 
			break; 
		}
		case OBJECT_TYPE_KOOPAS:
		{
			int model = (int)atof(tokens[4].c_str());
			obj = new CKoopas(x,y, model);
			DebugOut(L"[INFO] KOOPAS object created!\n");
			break; 
		}
		case OBJECT_TYPE_BRICK: {
			obj = new CBrick(x, y); 
			break;
		}
		case OBJECT_TYPE_PLATFORM: {
			float w = (float)atof(tokens[3].c_str());
			float h = (float)atof(tokens[4].c_str());
			obj = new Platform();
			DebugOut(L"[INFO] Platform object created!\n");
			break;
		}
		case OBJECT_TYPE_QUESTION_BRICK: {
			int model = (int)atof(tokens[4].c_str());
			obj = new CQuestionBrick(x, y, model);
			break;
		}
		case OBJECT_TYPE_COLOR_BLOCK:
		{
			float width = (float)atof(tokens[4].c_str());
			float height = (float)atof(tokens[5].c_str());

			obj = new CColorBlock(x, y, width, height);
			break;
		}
		case OBJECT_TYPE_PIPE: {
			int model = (int)atof(tokens[4].c_str());
			obj = new CPipe(x, y, model);
			break;
		}
		case OBJECT_TYPE_PORTAL: // đối tượng chuyển cảnh
		{
			float r = (float)atof(tokens[4].c_str());
			float b = (float)atof(tokens[5].c_str());
			float scene_id = (float)atoi(tokens[6].c_str()); // cảnh này giúp mình nhảy tới cảnh nào
			obj = new CPortal(x, y, r, b, scene_id);
		}
		case OBJECT_TYPE_COIN: {
			obj = new CCoin(x,y);
			break;
		}
		case OBJECT_TYPE_PLANT: {
			obj = new Plant(x, y); break; 
		}
		case OBJECT_TYPE_FIRE_PLANT: {
			int model = (int)atof(tokens[4].c_str());
			obj = new FirePlant(x, y, model); break;
		}
		case OBJECT_TYPE_COIN_BRICK: 
		{
			int model = (int)atof(tokens[4].c_str());
			obj = new CoinBrick(x, y, model); break; 
		}

		break;
		default:
			DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			return;
		}

		// General object setup
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	//}
	//f.close();
}



void CPlayScene::_ParseSection_TILEMAP(string line) {	//doc map tu file txt

	int ID, rowMap, columnMap, rowTile, columnTile, totalTile;
	LPCWSTR path = ToLPCWSTR(line);
	ifstream f(path, ios::in);
	f >> ID >> rowMap >> columnMap >> rowTile >> columnTile >> totalTile;
	float** tileMapData = new float* [rowMap];   // sửa kiểu dữ liệu int to float ở đây
	for (int i = 0; i < rowMap; i++) {
		tileMapData[i] = new float[columnMap];
		for (int j = 0; j < columnMap; j++) {
			f >> tileMapData[i][j];
		}
	}
	f.close();
	map = new Map(ID, rowMap, columnMap, rowTile, columnTile, totalTile);
	map->GetSpriteTile();	
	map->SetMap(tileMapData);
}

void CPlayScene::Load() // load file txt lên chương tình
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
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
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_DRAWMAP;
			continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section) // kiểm tra xem section đang là loại dữ liệu gì
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_DRAWMAP: _ParseSection_TILEMAP(line);
			break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png");

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
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

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	Camera* camera = new Camera(player, game, map);
	camera->Update(dt);

	gameTime->Update(dt);
	gameTimeRemain = GAME_TIME_LIMIT - gameTime->GetTime();
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	map->DrawMap();
	HUD* hud = new HUD(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() + SCREEN_HEIGHT - DISTANCE_FROM_BOTTOM_CAM_TO_TOP_BOARD);
	for (size_t i = 0; i < objects.size(); i++)
	{

		if (objects[i]->CheckObjectInCamera())
			objects[i]->Render();
	}
	hud->Render(player, gameTimeRemain);
}

/*
	Unload current scene
*/
void CPlayScene::Unload() // xóa hết tất cả các object
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	
	case DIK_RIGHT:
		mario->SetState(MARIO_STATE_IDLE);
		break;
	case DIK_LEFT:
		mario->SetState(MARIO_STATE_IDLE);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_RELEASE_RUN);
		if (mario->isHoldingTurtle) {
			mario->isHoldingTurtle = false;
		}
		break;
	case DIK_S:
		mario->isFallSlow = false;
		break;
	}

}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
			mario->y -= MARIO_BIG_BBOX_HEIGHT;
		}
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
			mario->y -= MARIO_BIG_BBOX_HEIGHT;
		}
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_4:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
			mario->y -= MARIO_BIG_BBOX_HEIGHT;
		}
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
	//set mario position for quick demo

	case DIK_5:
		mario->SetPosition(1900,327);
		break;
	case DIK_6:
		mario->SetPosition(1600, 128);
		break;
	case DIK_R:
		mario->Reset();
		break;
	case DIK_S: // hanh dong khi nhan phim nhay
		if (mario->GetLevel() == MARIO_LEVEL_RACOON) {
			if (mario->isFlying) {
				mario->isFlapping = true;
				mario->SetState(MARIO_RACOON_STATE_FLAPPING);
			}
			else if (mario->pendingFallSlow) {
				mario->SetState(MARIO_RACOON_STATE_FALL_SLOW);
			}
		}
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		if (!mario->isAttack) {
			if (mario->GetLevel() == MARIO_LEVEL_RACOON) {
				mario->SetState(MARIO_RACOON_STATE_ATTACK);
			}
		}
		if (mario->GetLevel() == MARIO_LEVEL_FIRE) {
			if (!mario->isShootingFireBall) {
				mario->SetState(MARIO_STATE_SHOOTING);
			}
		}
	}
}
	

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if(!mario->isRunning && game->IsKeyDown(DIK_A) &&!mario->isHoldingTurtle)
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		if (mario->isSitting) {
			mario->SetState(MARIO_STATE_SIT_RELEASE);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (!mario->isRunning && game->IsKeyDown(DIK_A) && !mario->isHoldingTurtle)
		{
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		if (mario->isSitting) {
			mario->SetState(MARIO_STATE_SIT_RELEASE);
		}
	}
	else if (game->IsKeyDown(DIK_S)) {

		mario->SetState(MARIO_STATE_JUMP);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
	
	
}


bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
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
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}