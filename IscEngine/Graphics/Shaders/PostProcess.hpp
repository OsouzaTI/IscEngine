#pragma once

#include "Base/Shader.hpp"
#include "../Textures/Texture.hpp"
#include "../Models/Mesh.hpp"

namespace IscEngine {

	// PostProcess
	class PostProcess {

		private:
			
			static Mesh* quad; // Simple quad that covers the screen

		public:

			// Initializes the static variables of the class
			static void initializeStatic();
			// Renders the Texture covering all the screen
			static void render(const Texture* const texture);

			//////////////////////////////////////////////////////////////////////////////////////////////

			// No constructor
			PostProcess() = delete;

	};

}