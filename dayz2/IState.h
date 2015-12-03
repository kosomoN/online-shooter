#pragma once

struct IState
{
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
};