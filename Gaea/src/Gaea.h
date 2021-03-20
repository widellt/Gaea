#pragma once

// For use by Gaea applications  //////

	// Application layer 
#include "Gaea/Application.h"
#include "Gaea/Layer.h"
#include "Gaea/Log.h"

// Time
#include "Gaea/Core/Timestep.h"

	// Inputs 
#include "Gaea/Input.h"
#include "Gaea/KeyCodes.h"
#include "Gaea/MouseButtonCodes.h"

	// ImGui
#include "Gaea/ImGui/ImGuiLayer.h"

// Rendering ///////////////////////////
#include "Gaea/Renderer/Renderer.h"
#include "Gaea/Renderer/RenderCommand.h"

	// Resources
#include "Gaea/Renderer/Shader.h"
#include "Gaea/Renderer/Texture.h"
#include "Gaea/Renderer/Buffer.h"
#include "Gaea/Renderer/VertexArray.h"

	// Other renderer primitives
#include "Gaea/Renderer/OrthographicCamera.h"

// ---------Entry Point---------
#include "Gaea/EntryPoint.h"
//------------------------------