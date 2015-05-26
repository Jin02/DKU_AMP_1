#pragma once

#include "Scene.h"
#include "ShaderFactory.hpp"

#include "SimpleSoundPlayer.h"
#include "SimpleText2D.h"

#include "System.h"

class TestScene : public Core::Scene
{
private:
	struct StageOnOffImage
	{
		UI::SimpleImage2D* onImg;
		UI::SimpleImage2D* offImg;
	};
	struct StageVisual
	{
		std::array<StageOnOffImage, 5> stageImgs;
	};

private:
	System*						_mipsEmulator;

private:
	UI::SimpleImage2D*							_background;
	UI::SimpleImage2D*							_pipelineStageNames;
	std::array<UI::SimpleImage2D*, 5>			_lineBack;
	std::array<UI::SimpleText2D*, 5>			_linePC;
	std::array<UI::SimpleText2D*, 5>			_lineDescribeInst;
	std::array<StageVisual, 5>					_lineStage;		

public:
	TestScene(void);
	~TestScene(void);

public:
	virtual void OnInitialize();
	virtual void OnRenderPreview();
	virtual void OnInput(const Device::Win32::Mouse& mouse, const  Device::Win32::Keyboard& keyboard);
	virtual void OnUpdate(float dt);
	virtual void OnRenderPost();
	virtual void OnDestroy();
};

