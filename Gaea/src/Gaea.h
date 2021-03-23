#pragma once

// For use by Gaea applications  //////

	// Application layer 
#include "Gaea/Core/Application.h"
#include "Gaea/Core/Layer.h"
#include "Gaea/Core/Log.h"

// Time
#include "Gaea/Core/Timestep.h"

	// Inputs 
#include "Gaea/Core/Input.h"
#include "Gaea/Core/KeyCodes.h"
#include "Gaea/Core/MouseButtonCodes.h"
#include "Gaea/Renderer/OrthographicCameraController.h"

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
#include "Gaea/Core/EntryPoint.h"
//------------------------------