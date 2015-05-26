#include "TestScene.h"
#include <fstream>
#include "ShaderManager.h"
#include "Mesh.h"
#include "LightCulling.h"

#include "Director.h"

using namespace Rendering;
using namespace UI;
using namespace Device;

TestScene::TestScene(void) : _mipsEmulator(nullptr), _pipelineStageNames(nullptr)
{

}

TestScene::~TestScene(void)
{
}

void TestScene::OnInitialize()
{
	_mipsEmulator = System::GetInstance();
	_mipsEmulator->Load("./MipsBinFiles/factorial.bin");

	auto CreateSimpleImage2D = [&](const std::string& name, const std::string& texturePath, const Math::Size<uint>& size)
	{
		SimpleImage2D* sim2d = new SimpleImage2D(name);
		sim2d->Initialize(size);

		Texture::Texture* texture 
			= _textureMgr->LoadTextureFromFile(texturePath, false);
		sim2d->UpdateMainImage(texture);
		return sim2d;
	};

	_background = CreateSimpleImage2D("Background", "Resources/Background.png", Director::GetInstance()->GetWindowSize());
	
	_pipelineStageNames = CreateSimpleImage2D("TopPipelineStageNames", "Resources/TopMenu.png", Math::Size<uint>(502, 100));
	_pipelineStageNames->GetTransform()->UpdatePosition(Math::Vector3(-32, 300, 0));

	for(int i=0; i<_lineBack.size(); ++i)
	{
		_lineBack[i] = CreateSimpleImage2D("PipelineBackground_" + std::to_string(i), "Resources/PipelineBackground.png", Math::Size<uint>(768, 104));
		_lineBack[i]->GetTransform()->UpdatePosition(Math::Vector3(0, (i - 2) * 100, 0));
	}

	auto CreateSimpleText2D = [&](const std::string& name, unsigned int length, const std::string& initText)
	{
		SimpleText2D* text = new SimpleText2D(name);
		text->Initialize(length);
		text->UpdateText(initText);

		return text;
	};

	for(int i=0; i<_linePC.size(); ++i)
	{
		_linePC[i] = CreateSimpleText2D("LinePC_" + std::to_string(i), 20, "");
		_linePC[i]->GetTransform()->UpdatePosition(Math::Vector3(-330, (i - 2) * 100 - 5, 0));
		_linePC[i]->GetTransform()->UpdateScale(Math::Vector3(1.5f, 1.5f, 0.0f));
	}

	for(int i=0; i<_lineDescribeInst.size(); ++i)
	{
		_lineDescribeInst[i] = CreateSimpleText2D("LineDescribe_" + std::to_string(i), 40, "");
		_lineDescribeInst[i]->GetTransform()->UpdatePosition(Math::Vector3(250, (i - 2) * 100 - 5, 0));
		_lineDescribeInst[i]->GetTransform()->UpdateScale(Math::Vector3(1.5f, 1.5f, 1.5f));
	}

	std::string iconNames[] =
	{
		"Fetch", "Decode", "Execute", "Memory", "Write"
	};
	for(int i=0; i<_lineStage.size(); ++i)
	{
		for(int j=0; j<_lineStage[i].stageImgs.size(); ++j)
		{
			std::string name = "StageOnIcon_" + std::to_string(i) + "_" + std::to_string(j);
			_lineStage[i].stageImgs[j].onImg	= CreateSimpleImage2D(name, "Resources/" + iconNames[j] + "On.png", Math::Size<uint>(96, 96));
			SimpleImage2D* on = _lineStage[i].stageImgs[j].onImg;
			on->GetTransform()->UpdatePosition(Math::Vector3( (j - 2) * 100 - 32, (i - 2) * 100, 0));

			//name = "StageOffIcon_" + std::to_string(i) + "_" + std::to_string(j);
			//_lineStage[i].stageImgs[j].offImg	= CreateSimpleImage2D(name, "Resources/" + iconNames[j] + "Off.png", Math::Size<uint>(100, 100));
			//SimpleImage2D* off = _lineStage[i].stageImgs[j].offImg;
		}
	}
}

void TestScene::OnRenderPreview()
{
}

void TestScene::OnInput(const Device::Win32::Mouse& mouse, const  Device::Win32::Keyboard& keyboard)
{
	if(keyboard.states[VK_SPACE] == KEYBOARD::Type::Up)
	{
		const uint pc = _mipsEmulator->GetProgramCounter();
		if(pc == 0xffffffff && _mipsEmulator->GetIsPipelineEmpty())
		{
			NextState();
			return;
		}

		_mipsEmulator->Run();
	}
}

void TestScene::OnUpdate(float dt)
{
}

void TestScene::OnRenderPost()
{

}

void TestScene::OnDestroy()
{
	SAFE_DELETE(_pipelineStageNames);
	SAFE_DELETE(_background);
	_mipsEmulator->Destroy();
}