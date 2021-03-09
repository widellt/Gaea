#include <Gaea.h>

class ExampleLayer : public Gaea::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override {
		GA_INFO("ExampleLayer::Update");
	}

	void OnEvent(Gaea::Event& event) override {
		GA_TRACE("{0}", event);
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
