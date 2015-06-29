#include "TestScene.h"
#include <fstream>
#include "ShaderManager.h"
#include "Mesh.h"
#include "LightCulling.h"

#include "Director.h"

#include <sstream>

using namespace Rendering;
using namespace UI;
using namespace Device;

TestScene::TestScene(void) : _mipsEmulator(nullptr), _pipelineStageNames(nullptr), _nextWork(false)
{
}

TestScene::~TestScene(void)
{
}

void TestScene::OnInitialize()
{
	_mipsEmulator = System::GetInstance();

	std::vector<std::string> disasamCodes;
	_mipsEmulator->Load("./MipsBinFiles/input3.bin", disasamCodes);

	auto CreateSimpleImage2D = [&](const std::string& name, const std::string& shardVertexKey, const std::string& texturePath, const Math::Size<uint>& size)
	{
		SimpleImage2D* sim2d = new SimpleImage2D(name);
		sim2d->Initialize(size, shardVertexKey);

		Texture::Texture* texture 
			= _textureMgr->LoadTextureFromFile(texturePath, false);
		sim2d->UpdateMainImage(texture);
		return sim2d;
	};

	_background = CreateSimpleImage2D("Background", "Background", "Resources/Background.png", Director::GetInstance()->GetWindowSize());
	
	_pipelineStageNames = CreateSimpleImage2D("TopPipelineStageNames", "TopPipelineStageNames", "Resources/TopMenu.png", Math::Size<uint>(502, 100));
	_pipelineStageNames->GetTransform()->UpdatePosition(Math::Vector3(36, 300, 0));

	for(int i=0; i<_lineBack.size(); ++i)
	{
		_lineBack[i] = CreateSimpleImage2D("PipelineBackground_" + std::to_string(i), "PipelineBackground", "Resources/PipelineBackground.png", Math::Size<uint>(632, 104));
		_lineBack[i]->GetTransform()->UpdatePosition(Math::Vector3(0, (i - 2) * 100, 0));
	}

	auto CreateSimpleText2D = [&](const std::string& name, const std::string& sharedVertexKey, unsigned int length, const std::string& initText)
	{
		SimpleText2D* text = new SimpleText2D(name);
		text->Initialize(length, sharedVertexKey);
		text->UpdateText(initText);

		return text;
	};

	for(int i=0; i<_linePC.size(); ++i)
	{
		std::string nameWithKey = "LinePC_" + std::to_string(i);
		_linePC[i] = CreateSimpleText2D(nameWithKey, nameWithKey, 10, "");
		_linePC[i]->GetTransform()->UpdatePosition(Math::Vector3(-270, -((i - 2) * 100) - 5, 0));
		_linePC[i]->GetTransform()->UpdateScale(Math::Vector3(1.5f, 1.5f, 0.0f));
	}

	std::string iconNames[] =
	{
		"Fetch", "Decode", "Execute", "Memory", "Write"
	};
	Math::Size<uint> size(96, 96);
	for(int i=0; i<_lineStage.size(); ++i)
	{
		for(int j=0; j<_lineStage[i].stageImgs.size(); ++j)
		{
			Math::Vector3 pos = Math::Vector3( (j - 2) * 100 + 36, -((i - 2) * 100), 0);

			std::string name = "StageOffIcon_" + std::to_string(i) + "_" + std::to_string(j);
			_lineStage[i].stageImgs[j].off	= CreateSimpleImage2D(name, "StageOffIcon", "Resources/" + iconNames[j] + "Off.png", size);

			name = "StageOnIcon_" + std::to_string(i) + "_" + std::to_string(j);
			_lineStage[i].stageImgs[j].on	= CreateSimpleImage2D(name, "StageOnIcon", "Resources/" + iconNames[j] + "On.png", size);
			_lineStage[i].stageImgs[j].on->SetUse(false);

			_lineStage[i].stageImgs[j].cancel = CreateSimpleImage2D(name, "StageCancelIcon", "Resources/Cancel.png", size);
			_lineStage[i].stageImgs[j].cancel->SetUse(false);

			_lineStage[i].stageImgs[j].stall = CreateSimpleImage2D(name, "StageStallIcon", "Resources/Stall.png", size);
			_lineStage[i].stageImgs[j].stall->SetUse(false);

			for(int k=0; k<4; ++k)
				_lineStage[i].stageImgs[j].icons[k]->GetTransform()->UpdatePosition(pos);
		}
	}

	for(int i=0; i<32; ++i)
	{
		std::string nameKey = "Register_" + std::to_string(i);
		_registerText[i] = CreateSimpleText2D(nameKey, nameKey, 50, "");
		_registerText[i]->GetTransform()->UpdatePosition(Math::Vector3(-450, -((i - 16) * 20), 0));
		_registerText[i]->GetTransform()->UpdateScale(Math::Vector3(1.5f, 1.5f, 1.0f));
	}

	for(int i=0; i<50; ++i)
	{
		std::string nameKey = "Disassam_" + std::to_string(i);

		std::string disCode = "";
		if( i < disasamCodes.size() )
		{
			disCode = disasamCodes[i];

			_disassamText[i] = CreateSimpleText2D(nameKey, nameKey, 50, disCode);
			_disassamText[i]->GetTransform()->UpdatePosition(Math::Vector3(500, -((i - 16) * 17) + 50, 0));
			_disassamText[i]->GetTransform()->UpdateScale(Math::Vector3(0.9f, 0.9f, 1.0f));
		}
	}
}

void TestScene::OnRenderPreview()
{
}

void TestScene::RunOneCycle()
{
	const uint pc = _mipsEmulator->GetProgramCounter();
	if(_mipsEmulator->CheckAllEndInst())
	{
		_nextWork = false;
		NextState();
		return;
	}

	auto UpdateUI = [&](const System::PipelineStageInfo& stageInfo, uint indexInList)
	{
		// Box Icons
		{
			auto& line = _lineStage[indexInList];
			for(int i=0; i<5; ++i)
			{
				line.stageImgs[i].on->SetUse(false);
				line.stageImgs[i].cancel->SetUse(false);
			}

			if(stageInfo.isEnd == false)
			{
				if( stageInfo.pip->GetIsCancel() == false )
				{
					line.stageImgs[ (uint)stageInfo.pip->GetState() ].on->SetUse(true);
				}
				else
				{
					for(int i=0; i<5; ++i)
						line.stageImgs[i].cancel->SetUse(true);
				}
			}
		}

		if(stageInfo.isEnd == false)
		{
			if( stageInfo.pip->GetIsCancel() )
			{
				_linePC[indexInList]->UpdateText("Stall");
			}
			else
			{
				uint pc = stageInfo.pip->GetProgramCounter();
				{
					std::stringstream stream;
					stream << std::hex << pc;
					std::string result( stream.str() );
					result.insert(0, "0x");
					_linePC[indexInList]->UpdateText(result);
				}
			}
		}
		else
		{
			_linePC[indexInList]->UpdateText("None");
		}
	};

	auto RegisterTextUpdate = [&]()
	{
		for(int i=0; i<32; ++i)
		{
			std::stringstream stream;
			stream << std::hex << _mipsEmulator->GetDataFromRegister(i);
			std::string regValueText(stream.str());

			_registerText[i]->UpdateText( "register[" + std::to_string(i) + "] = 0x" + regValueText );
		}
	};

	_mipsEmulator->Run(UpdateUI, RegisterTextUpdate);
}

void TestScene::OnInput(const Device::Win32::Mouse& mouse, const  Device::Win32::Keyboard& keyboard)
{
	if(keyboard.states[VK_SPACE] == KEYBOARD::Type::Up)
	{
		_nextWork = true;
	}
}

void TestScene::OnUpdate(float dt)
{
	if(_nextWork)
	{
		RunOneCycle();
		_nextWork = false;
	}
}

void TestScene::OnRenderPost()
{
}

void TestScene::OnDestroy()
{
	HWND handle = Director::GetInstance()->GetWin()->GetHandle();
	std::string resultText = "Result Value is " + std::to_string(_mipsEmulator->GetDataFromRegister(2));
	MessageBox(handle, resultText.c_str(), "Result", MB_OK);

	for(int i=0; i<5; ++i)
	{
		SAFE_DELETE(_lineBack[i]);
		SAFE_DELETE(_linePC[i]);
	}

	for(int i=0; i<5; ++i)
	{
		for(int j=0; j<5; ++j)
		{
			for(int k=0; k<4; ++k)
			{
				SAFE_DELETE(_lineStage[i].stageImgs[j].icons[k]);
			}
		}
	}

	for(int i=0; i<32; ++i)
		SAFE_DELETE(_registerText[i]);

	SAFE_DELETE(_pipelineStageNames);
	SAFE_DELETE(_background);
	_mipsEmulator->Destroy();

	Director::GetInstance()->Exit();
}