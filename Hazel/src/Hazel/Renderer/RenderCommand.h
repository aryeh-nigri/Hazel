#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexAray)
		{
			s_RendererAPI->DrawIndexed(vertexAray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}