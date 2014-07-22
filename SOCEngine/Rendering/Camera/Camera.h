#pragma once

#include "DX.h"
#include "Component.h"
#include "Frustum.h"
#include "LightManager.h"
#include "Component.h"

namespace Rendering
{
	class Camera : public Core::Component
	{
	public:
		static const Core::Component::Type GetComponentType() {	return Core::Component::Type::Camera;	}

	public:
		enum Type { Perspective, Orthographic };
		enum ClearFlag { FlagSkybox, FlagSolidColor, FlagTarget, FlagDontClear };
		//CLEAR_FLAG_DEPTHONLY�� ������. ��� �����϶�°��� �� �𸣰��� -��-;

	private:
		Frustum					*frustum;
		//Shader::Shader			*rtShader;
		//Texture::RenderTarget	*renderTarget;

	public:  //���� private�� �� �ʿ�� ����.
		float				FOV;
		float				clippingNear;
		float				clippingFar;
		ClearFlag			clearFlag;
		Type				camType;
		float				aspect;
		Color				clearColor;

	public:
		Camera();
		~Camera(void);

	private:
		void CalcAspect();
		void Clear(Device::DX *dx);
		void RenderObjects(std::vector<Core::Object*>::iterator &objectBegin,	std::vector<Core::Object*>::iterator &objectEnd,	Light::LightManager* sceneLights);

	public:
		void ProjectionMatrix(Math::Matrix &outMatrix);
		void ViewMatrix(Math::Matrix& outMatrix);

	public:
		//static void SceneUpdate(float dt, std::vector<Object*> *sceneObjects);
		static void SceneRender(Camera *cam, 
			std::vector<Core::Object*>::iterator &objectBegin,
			std::vector<Core::Object*>::iterator &objectEnd,
			Light::LightManager* sceneLights);

		void Render(std::vector<Core::Object*>::iterator &objectBegin,
			std::vector<Core::Object*>::iterator &objectEnd,
			Light::LightManager* sceneLights);

	public:
		virtual void Initialize();
		virtual void Destroy();
//		virtual Component::Type GetComponentType();
	};
}