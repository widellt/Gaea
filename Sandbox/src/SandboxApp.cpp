#include <Gaea.h>

class Sandbox : public Gaea::Application {

public:
	Sandbox() {

	}
	
	~Sandbox() {

	}

};

Gaea::Application* Gaea::CreateApplication() {
	return new Sandbox();
}
