#pragma once
// EXTERNAL INCLUDES
#include <d3dcompiler.h>
#include <d3d11.h>
// INTERNAL INCLUDES
#include "component.h"
#include "math/types.h"
#include "mesh.h"
#include "graphics/stb_image.h"
#include "utils/util.h"
#include "d3d11renderer.h"
#include "graphics/bsdfmaterial.h"
namespace Engine::ECS
{
	class MeshRenderer
	{
	public:
		~MeshRenderer()
		{
			//for (GraphicsBufferPtr& vb : vertexBuffers)
			//{
			//	Engine::Graphics::Renderer::GetInstancePtr()->ReleaseBuffer(vb);
			//}
			//vertexBuffers.clear();
			//for (GraphicsBufferPtr& ib : indexBuffers)
			//{
			//	Engine::Graphics::Renderer::GetInstancePtr()->ReleaseBuffer(ib);
			//}
			//indexBuffers.clear();
			//indexCounts.clear();
		}
		MeshRenderer(){}
		MeshRenderer(const MeshRenderer& copy) = default;
		MeshRenderer& operator=(const MeshRenderer& copy) = default;
		void SetMesh(Engine::Resources::Mesh mesh)
		{
			this->mesh = mesh;
			for (GraphicsBufferPtr& vb : vertexBuffers)
			{
				Engine::Graphics::Renderer::GetInstancePtr()->ReleaseBuffer(vb);
			}
			vertexBuffers.clear();
			for (GraphicsBufferPtr& ib : indexBuffers)
			{
				Engine::Graphics::Renderer::GetInstancePtr()->ReleaseBuffer(ib);
			}
			indexBuffers.clear();
			indexCounts.clear();
			for (Engine::Resources::Mesh::SubMesh sm : this->mesh.subMeshes)
			{
				GraphicsBufferPtr vb = Engine::Graphics::Renderer::GetInstancePtr()->CreateBuffer(Engine::Graphics::BufferType::Vertex, sm.vertices.data(), static_cast<ui32>(sm.vertices.size()) * sizeof(Vertex));
				vertexBuffers.push_back(vb);
				GraphicsBufferPtr ib = Engine::Graphics::Renderer::GetInstancePtr()->CreateBuffer(Engine::Graphics::BufferType::Index, sm.indices.data(), static_cast<ui32>(sm.indices.size()) * sizeof(ui32));
				indexBuffers.push_back(ib);
				indexCounts.push_back(static_cast<ui32>(sm.indices.size()));
			}
		}
		static ui32 GetTypeID()
		{
			return 2;
		}
		std::vector< Engine::Graphics::BsdfMaterial> materials;
		Engine::Resources::Mesh mesh;
	private:
		std::vector<GraphicsBufferPtr> vertexBuffers;
		std::vector<GraphicsBufferPtr> indexBuffers;
		std::vector<ui32> indexCounts;
		//friend class Engine::Graphics::D3D11Renderer;
	protected:
		friend class MeshSystem;
	};
}