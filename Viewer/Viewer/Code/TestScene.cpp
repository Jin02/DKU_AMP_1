#include "TestScene.h"
#include <fstream>
#include "ShaderManager.h"
#include "Mesh.h"
#include "LightCulling.h"

#include "Director.h"

using namespace Rendering;
using namespace UI;
using namespace Device;

TestScene::TestScene(void)
	: _mipsEmulator(nullptr)
{

}

TestScene::~TestScene(void)
{
}

void TestScene::OnInitialize()
{
	_mipsEmulator = System::GetInstance();
	_mipsEmulator->Load("./MipsBinFiles/factorial.bin");

	_background = new SimpleImage2D("Background");

	Director* director = Director::GetInstance();
	Math::Size<uint> winSize = director->GetWindowSize();
	_background->Initialize(winSize);

	Texture::Texture* backgroundImg 
		= _textureMgr->LoadTextureFromFile("Resources/Background.png", false);
	_background->UpdateMainImage(backgroundImg);
}

void TestScene::OnRenderPreview()
{
}

void TestScene::OnInput(const Device::Win32::Mouse& mouse, const  Device::Win32::Keyboard& keyboard)
{
}

void TestScene::OnUpdate(float dt)
{
	//const uint pc = _mipsEmulator->GetProgramCounter();
	//if(pc == 0xffffffff && _mipsEmulator->GetIsPipelineEmpty())
	//{
	//	NextState();
	//	return;
	//}

	//_mipsEmulator->Run();
}

void TestScene::OnRenderPost()
{

}

void TestScene::OnDestroy()
{
	SAFE_DELETE(_background);
	_mipsEmulator->Destroy();
}