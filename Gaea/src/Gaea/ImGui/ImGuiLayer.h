#pragma once

#include "Gaea/Layer.h"

namespace Gaea {
	class GAEA_API ImGuiLayer : public Layer 
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		float _Time = 0.0f;
	};
}


