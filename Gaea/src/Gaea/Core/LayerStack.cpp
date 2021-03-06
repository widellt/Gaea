#include "gapch.h"
#include "LayerStack.h"


namespace Gaea {
	LayerStack::LayerStack() {
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : _Layers) {
			layer->OnDetach();
			delete layer;
		}
			
	}

	void LayerStack::PushLayer(Layer* layer) {
		_Layers.emplace(_Layers.begin() + _LayerInsertIndex, layer);
		_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		// Overlays should be rendered after layers
		_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(_Layers.begin(), _Layers.end(), layer);
		if (it != _Layers.end()) {
			_Layers.erase(it);
			_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(_Layers.begin(), _Layers.end(), overlay);
		if (it != _Layers.end()) {
			_Layers.erase(it);
		}
	}
}