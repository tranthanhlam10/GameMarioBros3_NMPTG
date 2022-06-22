#include "PButton.h"
#include "CoinBrick.h"
#include "PlayScence.h"
#include "MushRoom.h"

PButton::PButton(float x, float y) :CGameObject(x, y)
{
	this->ay = 0;
	this->ax = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_PBUTTON_FROM_TXT));
}

void PButton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + P_BUTTON_BBOX_WIDTH;
	bottom = top + P_BUTTON_BBOX_HEIGHT;
	if (isPressed) {
		left = top = right = bottom = 0;
	}
}

int PButton::IsCollidable() {
	if (isPressed) {
		return 0;
	}
	else {
		return 1;
	}
}



void PButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isCoinBrickTransform) {
		y = y + (P_BUTTON_BBOX_HEIGHT - P_BUTTON_IS_PRESSED_BBOX_HEIGHT);

		for (size_t i = 0; i < scene->objects.size(); i++) {
			if (scene->objects[i]->GetType() == COINBRICK) {
				CoinBrick* coinBrick = dynamic_cast<CoinBrick*>(scene->objects[i]);
				if (coinBrick->GetModel() == COIN_BRICK_COIN) {
					coinBrick->SetState(COIN_BRICK_STATE_TRANSFORM_COIN);
				}
			}
		}
		isCoinBrickTransform = false;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


int PButton::IsBlocking() {
	if (isPressed) {
		return 0;
	}
	else {
		return 1;
	}
}

void PButton::Render()
{
	int ani = P_BUTTON_ANI;

	if (isPressed) {
		ani = P_BUTTON_ANI_IS_PRESSED;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}