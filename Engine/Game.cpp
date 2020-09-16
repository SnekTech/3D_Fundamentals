/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Mat2.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	const float dTheta = 2.0 * PI / (2 * nFlares);
	for (int i = 0; i < 2 * nFlares; i++)
	{
		const float radius = i % 2 == 0 ? radOuter : radInner;
		star.emplace_back(
			radius * cos(dTheta * (float)i),
			radius * sin(dTheta * (float)i)
		);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		theta += vRot;
	}
}

void Game::ComposeFrame()
{
	const Vec2 translate = { float(gfx.ScreenWidth) / 2.0f, float(gfx.ScreenHeight) / 2.0f };
	const Mat2 transform = Mat2::Rotation(theta) * Mat2::Scaling(size);
	auto vtx(star);
	for (auto& v : vtx)
	{
		v *= transform;
		v += translate;
	}
	for (auto i = vtx.cbegin(), end = std::prev(vtx.cend()); i != end; i++)
	{
		gfx.DrawLine(*i, *std::next(i), Colors::White);
	}
	gfx.DrawLine(vtx.front(), vtx.back(), Colors::White);
}