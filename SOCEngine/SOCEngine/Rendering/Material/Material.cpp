#include "Material.h"
#include "Utility.h"
#include "Director.h"

using namespace Rendering;
using namespace Rendering::Buffer;

Material::Material(const std::string& name)	
	: _vertexShader(nullptr), _pixelShader(nullptr), _name(name),
	_updateConstBufferMethod(UpdateCBMethod::Default),
	_hasAlpha(false), _changedAlpha(true)
{
}

Material::~Material(void)
{

}

void Material::Init(const std::vector<unsigned int>& vsConstBufferUsageIndices, const std::vector<unsigned int >& psConstBufferUsageIndices,
					const std::vector<unsigned int>& vsTextureUsageIndices,		const std::vector<unsigned int>& psTextureUsageIndices)
{
	InitConstBufferSlot(vsConstBufferUsageIndices, psConstBufferUsageIndices);
	InitTextureSlot(vsTextureUsageIndices, psTextureUsageIndices);
}

void Material::InitConstBufferSlot(const std::vector<unsigned int>& vsTextureUsageIndices, const std::vector<unsigned int >& psTextureUsageIndices)
{
	for(auto& idx : vsTextureUsageIndices)
		_constbuffers.usageVS.push_back( std::make_pair(idx, nullptr) );

	for(auto& idx : psTextureUsageIndices)
		_constbuffers.usagePS.push_back( std::make_pair(idx, nullptr) );
}

void Material::InitTextureSlot(const std::vector<unsigned int>& vsShaderSlotIndex, const std::vector<unsigned int>& psShaderSlotIndex)
{
	for(auto& idx : vsShaderSlotIndex)
		_textures.usageVS.push_back(  std::make_pair(idx, nullptr) );

	for(auto& idx : psShaderSlotIndex)
		_textures.usagePS.push_back(  std::make_pair(idx, nullptr) );
}

void Material::ClearResource(ID3D11DeviceContext* context)
{
	_vertexShader->ClearResource(context, &_textures.usageVS);
	_pixelShader->ClearResource(context, &_textures.usagePS);
}

void Material::UpdateShader(ID3D11DeviceContext* context)
{
	_vertexShader->UpdateShader(context);
	_pixelShader->UpdateShader(context);
}

void Material::UpdateResources(ID3D11DeviceContext* context)
{
	_vertexShader->UpdateResources(context, &_constbuffers.usageVS, &_textures.usageVS);

	Sampler* sampler = Device::Director::GetInstance()->GetCurrentScene()->GetSampler();
	std::vector<Shader::PixelShader::SamplerType> samplers;

	//임시로, 0번에 linear만 넣음.
	samplers.push_back(std::make_pair(0, sampler));


	_pixelShader->UpdateResources(context, &_constbuffers.usagePS, &_textures.usagePS, samplers);
}

const Rendering::Texture::Texture* Material::FindTexture(unsigned int& outArrayIndex, unsigned int shaderSlotIndex, UsageTextureType usageType)
{
	const std::vector<Shader::BaseShader::TextureType>* textures = nullptr;

	if(usageType == UsageTextureType::Vertex)
		textures = &_textures.usageVS;
	else if(usageType == UsageTextureType::Pixel)
		textures = &_textures.usagePS;

	if(textures)
	{
		for(unsigned int i=0; i<textures->size(); ++i)
		{		
			if(textures->at(i).first == shaderSlotIndex)
			{
				outArrayIndex = i;
				return textures->at(i).second;
			}
		}
	}

	DEBUG_LOG("Material FindTexture Error : Undefined UsageTextureType");
	outArrayIndex = 0;
	return nullptr;
}

bool Material::UpdateTextureUseShaderSlotIndex(unsigned int shaderSlotIndex, const Rendering::Texture::Texture* texture, UsageTextureType usageType)
{
	unsigned int arrayIdx = 0;
	auto map = FindTexture(arrayIdx, shaderSlotIndex, usageType);

	bool success = false;

	if(map)
	{
		if(usageType == UsageTextureType::Vertex)
		{
			_textures.usageVS[arrayIdx].second = texture;
			success = true;

		}
		else if(usageType == UsageTextureType::Pixel)
		{
			_textures.usagePS[arrayIdx].second = texture;
			success = true;
		}
	}

	if(success == false)
		DEBUG_LOG("Material UpdateTexture Error : cant update texture. you must check code in Material::FindTexture");

	return success;
}

bool Material::UpdateTextureUseArrayIndex(unsigned int arrayIndex, const Rendering::Texture::Texture* texture, UsageTextureType usageType)
{
	std::vector<Shader::BaseShader::TextureType>* textures = nullptr;

	if(usageType == UsageTextureType::Vertex)
		textures = &_textures.usageVS;
	else if(usageType == UsageTextureType::Pixel)
		textures = &_textures.usagePS;
	else
		DEBUG_LOG("Material UpdateTexture Error : undefined UsageTextureType");

	if(textures)
	{
		Shader::BaseShader::TextureType& textureData = textures->at(arrayIndex);
		textureData.second = texture;
	}

	return textures != nullptr;
}