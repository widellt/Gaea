#pragma once

#include "Gaea/Layer.h"

#include "Gaea/Events/KeyEvent.h"
#include "Gaea/Events/MouseEvent.h"
#include "Gaea/Events/ApplicationEvent.h"

namespace Gaea {
	class GAEA_API ImGuiLayer : public Layer 
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnImGuiRender() override;
		void Begin();
		void End();
	private:
	private:
		float _Time = 0.0f;
	};
}


