#pragma once

#include "Gaea/Core.h"
#include "Gaea/Events/Event.h"

namespace Gaea {
	class GAEA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return _DebugName; }
	protected:
		std::string _DebugName;
	};
}


