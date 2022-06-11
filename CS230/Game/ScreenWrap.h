/*--------------------------------------------------------------
Copyright(C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.h
Project: CS230
Author: Kevin Wright
Creation date: 2/17/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Component.h"

namespace CS230
{
	class GameObject;
}

class ScreenWrap : public CS230::Component {
public:
	ScreenWrap(CS230::GameObject& object) : object(object) {}
	void Update(double dt) override;
private:
	CS230::GameObject& object;
};