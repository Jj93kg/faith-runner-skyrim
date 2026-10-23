#pragma once

// For a plugin that builds Faith's host code together with more of its own (Superhot Faith: Superhot's time rules on
// top of Faith). It fills these in from a static initialiser; Faith Runner Skyrim itself leaves them all unset and
// behaves exactly as before.
namespace faith
{
	struct HostHooks
	{
		// The host sets Skyrim's global time multiplier itself: Reaction Time is switched off, so the two never fight.
		bool ownsTime = false;
		// The delta Faith steps with (her movement, animation, input and timers), given Skyrim's frame delta. Unset:
		// Skyrim's own delta, so Faith slows with the world.
		float (*stepDelta)(float a_gameDelta) = nullptr;
		// This frame's controls, just before Faith steps on them: the host can take a press for itself (clear it, and
		// Faith never sees it).
		void (*filterInput)(RE::PlayerCharacter* a_player, FaithInput& a_input) = nullptr;
		// After Faith's frame in PlayerCharacter::Update, every frame. a_input is null when Faith didn't step: she's
		// off, a menu is open, or Skyrim has the player (furniture, horse, kill move...); a_frame is her last frame.
		void (*afterFrame)(RE::PlayerCharacter* a_player, bool a_active, const FaithInput* a_input, const FaithFrame* a_frame, float a_delta) = nullptr;
		// Faith switched on or off.
		void (*enabled)(bool a_on) = nullptr;
		// After Faith's own Install (kDataLoaded) and after a save loads.
		void (*dataLoaded)() = nullptr;
		void (*gameLoaded)() = nullptr;
	};

	inline HostHooks& Host()
	{
		static HostHooks hooks;
		return hooks;
	}
}
