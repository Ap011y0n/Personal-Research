#include "j1Render.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "Animation.h"
#include "p2Log.h"
#include "j1EntityManager.h"
#include "j1Entity.h"
#include "Test_1.h"
#include "DynamicEnt.h"
#include "Brofiler/Brofiler.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Input.h"

Test_1::Test_1(int posx, int posy) : DynamicEnt(DynamicEntityType::TEST_1)
{
	name.create("test_1");

	actualState = ST_TEST_1_IDLE;
	speed = { 0, 0 };
	cost = 1;
	position.x = posx;
	position.y = posy;
	to_delete = false;
	isSelected = false;
	selectable = true;
	// Load all animations
}

Test_1::~Test_1()
{}

bool Test_1::Start()
{
	

	

	return true;
}

bool Test_1::Update(float dt)
{
	BROFILER_CATEGORY("UpdateTest_1", Profiler::Color::BlanchedAlmond);
	speed = { 0, 0 };

	CheckAnimation(dt);

	//App->render->Blit(App->entity->test_1_graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), 1.0f);
	
	
	if (position.x > 800)
		to_delete = true;


	if (isSelected && App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		App->input->GetMousePosition(mouse.x, mouse.y);
		mouse = App->map->WorldToMap(mouse.x, mouse.y);
		App->pathfinding->CreatePath(origin, mouse);
		path = App->pathfinding->GetLastPath();
		followpath = 1;
		move = true;
	}

	origin = App->map->WorldToMap(position.x, position.y);

	if (move)
	{

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint nextPoint = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			if (i == followpath)
			{
				App->render->DrawQuad({ nextPoint.x + 14, nextPoint.y + 14, 12, 12 }, 200, 0, 0, 100);
			}
			else {
				App->render->DrawQuad({ nextPoint.x + 14, nextPoint.y + 14, 6, 6 }, 200, 0, 0, 100);

			}
		}
		if (path->At(followpath) != NULL)
		{
			//This makes a comparison with the players position to make the correct move
			if (path->At(followpath)->x < origin.x) {
				speed.x -= 2;
			}

			if (path->At(followpath)->x > origin.x) {
				speed.x += 2;
			}

			if (path->At(followpath)->y < origin.y) {
				speed.y -= 2;
			}

			if (path->At(followpath)->y > origin.y) {
				speed.y += 2;
			}
			if (origin.x == path->At(followpath)->x && origin.y == path->At(followpath)->y)
				followpath++;
		}
	}

	
	position.y += speed.y;
	position.x += speed.x;
	if (isSelected)
		App->render->DrawCircle(position.x + 5, position.y + 5, 10, 0, 200, 0, 200);

	App->render->DrawQuad({ position.x, position.y, 10, 10 }, 200, 200, 0);
	


	

	return true;
}

bool Test_1::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateTest_1", Profiler::Color::BurlyWood)

	return true;
}

void Test_1::CheckAnimation(float dt)
{

}

bool Test_1::CleanUp()
{

	return true;
}