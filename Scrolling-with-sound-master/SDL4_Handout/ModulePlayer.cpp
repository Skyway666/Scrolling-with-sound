#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations

	// walk backwards animation (arcade sprite sheet)
	//backward.frames.PushBack({9, 136, 53, 83});
	backward.PushBack({ 628, 129, 60, 90 });
	backward.PushBack({ 711, 128, 59, 90 });
	backward.PushBack({ 797, 127, 57, 90 });
	backward.PushBack({ 883, 128, 58, 91 });
	backward.PushBack({ 974, 129, 57, 89 });
	backward.speed = 0.1f;

	// jump animation (arcade sprite sheet)
	jump.PushBack({ 99, 822, 60, 116 });
	jump.PushBack({ 175, 804, 48, 116 });//90
	jump.PushBack({ 249, 797, 57, 116 });//79
	jump.PushBack({ 325, 811, 52, 116 });//71
	jump.PushBack({ 395, 808, 51, 116 });//92
	jump.PushBack({ 462, 817, 58, 116 });//112
	jump.speed = 0.15f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if ((App->input->keyboard[SDL_SCANCODE_D] == 1) && (App->input->keyboard[SDL_SCANCODE_SPACE] != 1))
	{
		current_animation = &forward;
		position.x += speed;
	}

	if ((App->input->keyboard[SDL_SCANCODE_A] == 1) && (App->input->keyboard[SDL_SCANCODE_SPACE] != 1))
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if ((App->input->keyboard[SDL_SCANCODE_SPACE] == 1) && (App->input->keyboard[SDL_SCANCODE_D] != 1) && (App->input->keyboard[SDL_SCANCODE_A] != 1))
	{
		up = 1;
		jumping = 1;
	}
	if (jumping == 1)
	{ 
		current_animation = &jump;
    	if (up == 1)
		{ 
		   position.y -= speed*3;
          if (position.y < 150)
		   {
			   up = 0;
		   }
		}
		if (up == 0)
		{
		   position.y += speed*3;
		   if (position.y == 220)
		   {
			   up = 1;
			   jumping = 0;
		   }
		}
	}	
	


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	
	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}