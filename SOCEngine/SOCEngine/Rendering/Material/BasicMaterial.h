#pragma once

#include "Material.h"

namespace Rendering
{
	class BasicMaterial : public Material
	{
	public:
		//�� ������ �ε��� �����ε� ���Դϴ�.
		//Common.hlsl�� ���ǵǾ� �ִ� �������� �ε����� ����Ǿ� �ֽ��ϴ�.
		enum class VSConstBufferSlot : unsigned int
		{
			Transform		= 0,
			Camera			= 1,

			COUNT,
		};

		//�� ������ �ε��� �����ε� ���Դϴ�.
		//Common.hlsl�� ���ǵǾ� �ִ� �������� �ε����� ����Ǿ� �ֽ��ϴ�.
		enum class PSConstBufferSlot : unsigned int
		{
			MaterialColor	= 0,
			Camera			= 1,

			COUNT,
		};


	public:
		struct Color
		{
			//a value is alpha
			Rendering::Color main;

			//a value is shiness
			Rendering::Color specular;

			Color();
			~Color();
		};

	private:
		Color					_color;
		Buffer::ConstBuffer*	_colorBuffer;

	public:
		BasicMaterial(const std::string& name);
		BasicMaterial(const std::string& name, const Color& color);
		~BasicMaterial(void);

	public:
		void Init(ID3D11DeviceContext* context);
		void UpdateColorBuffer(ID3D11DeviceContext* context);
		void UpdateColor(const Color& color);

		void UpdateBasicConstBuffer(ID3D11DeviceContext* context, const Buffer::ConstBuffer* transform, const Buffer::ConstBuffer* camera);

		void UpdateAmbientMap(const Texture::Texture* tex);
		void UpdateDiffuseMap(const Texture::Texture* tex);
		void UpdateNormalMap(const Texture::Texture* tex);
		void UpdateSpecularMap(const Texture::Texture* tex);
		void UpdateOpacityMap(const Texture::Texture* tex);

	public:
		GET_ACCESSOR(ColorBuffer, Buffer::ConstBuffer*, _colorBuffer);
		GET_ACCESSOR(Color, const Color&, _color);
	};
}