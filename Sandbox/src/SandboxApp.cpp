#include <Gaea.h>

#include "imgui/imgui.h"

class ExampleLayer : public Gaea::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override {
		//GA_INFO("ExampleLayer::Update");
		if (Gaea::Input::IsKeyPressed(GA_KEY_TAB))
			GA_TRACE("Tab key is pressed! (poll)");
	}

	virtual void OnImGuiRender() override {
		
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Gaea::Event& event) override {
		//GA_TRACE("{0}", event);
		if (event.GetEventType() == Gaea::EventType::KeyPressed) {
			Gaea::KeyPressedEvent& e = (Gaea::KeyPressedEvent&) event;
			if(e.GetKeyCode() == GA_KEY_TAB)
				GA_TRACE("Tab key is pressed! (event)");
			GA_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Gaea::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}

};

Gaea::Application* Gaea::CreateApplication() {
	return new Sandbox();
}
