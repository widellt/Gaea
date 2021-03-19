#include "gapch.h"
#include "Renderer.h"

namespace Gaea{

	Renderer::SceneData* Renderer::_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera){
		_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", _SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		matInst.Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}