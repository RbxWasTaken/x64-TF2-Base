#pragma once
template<typename Type>
class CVar
{
public:
	const char* feature_name;
	Type Value;
};

namespace vars
{
	namespace aimbot
	{
		static bool draw_fov = false;
		static float fov_scale = 5.0f;
	}

	namespace menu 
	{
		static bool close_button = false;
		static bool fps_window = false;
	}

	namespace misc
	{
		static bool sv_cheats = false;
		static bool mvm_respawn = false;
		static bool flip_medal = false;
	}

	namespace visuals
	{
		static bool enable_visuals = false;
		static bool third_person = false;
		static bool weapon_sway = false;
		static bool flip_viewmodels = false;
	}
}

namespace features
{
	namespace visuals
	{
		inline CVar<bool> enable_visuals{ "Enable Visuals", false };
		inline CVar<bool> enable_player{ "Enable Players", false };
		inline CVar<bool> enable_buildings{ "Enable Buildings", false };
	}
	namespace misc
	{
		inline CVar<bool> bunny_hop{ "Bunny Hop", false };
		inline CVar<bool> auto_strafe{ "Auto Strafe", false };
		inline CVar<bool> clean_screenshots{ "Clean Screenshots", true};
	}
}