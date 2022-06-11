/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.h
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include <vector>

namespace CS230 {
	class InputKey {
	public:
		enum class Keyboard {
			None, Enter, Escape, Space, Left, Up, Right, Down,
			A, B, C, D, E, F, G, H, I, J,
			K, L, M, N, O, P, Q, R, S, T,
			U, V, W, X, Y, Z, Tilde,
			Count
		};

		InputKey(Keyboard button);
		bool IsKeyDown() const;
		bool IsKeyReleased() const;
	private:
		Keyboard button;
	};

	class Input {
	public:
		Input();
		bool IsKeyDown(InputKey::Keyboard key) const;
		bool IsKeyReleased(InputKey::Keyboard key) const;
		void SetKeyDown(InputKey::Keyboard key, bool value);
		void Update();
	private:
		std::vector<bool> keyDown;
		std::vector<bool> wasKeyDown;
	};
}