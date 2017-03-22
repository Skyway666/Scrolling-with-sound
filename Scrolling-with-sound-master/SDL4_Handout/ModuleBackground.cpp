#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// ship
	ship.x = 8;
	ship.y = 24;
	ship.w = 528;
	ship.h = 204;

	// girl animation
	girl.PushBack({ 624, 16, 31, 55 });
	girl.PushBack({ 624, 80, 31, 55 });
	girl.PushBack({ 624, 144, 31, 55 });
	girl.PushBack({ 624, 80, 31, 55 });
	girl.speed = 0.05f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect

	App->render->Blit(graphics, 0, var, &ship, 0.75f);

	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	
	App->render->Blit(graphics, 192, 104 + var, &(girl.GetCurrentFrame()), 0.75f); // girl animation

	App->render->Blit(graphics, 0, 170, &ground);

	if (true == up)
	{
		var += 0.15f;
		if (var >= 0)
			up = false;
	}
	else if (false == up)
	{
		var -= 0.15f;
		if (var <= -5.4)
			up = true;
	}

	return UPDATE_CONTINUE;
}