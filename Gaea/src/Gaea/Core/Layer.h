#pragma once

#include "Gaea/Core/Core.h"
#include "Gaea/Events/Event.h"

#include "Gaea/Core/Timestep.h"

namespace Gaea {
	class GAEA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}
		inline const std::string& GetName() const { return _DebugName; }
	protected:
		std::string _DebugName;
	};
}


