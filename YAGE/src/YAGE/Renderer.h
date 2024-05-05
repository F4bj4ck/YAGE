#pragma once
#include <memory>

#include "VulkanContext.h"
#include "Window.h"

namespace Yage
{
    class Renderer
    {
    public:
        Renderer(GLFWwindow* window);
        ~Renderer();

        void Render();
        void Resize();
        
        static Renderer* Create(GLFWwindow* window);
    private:
        std::unique_ptr<VulkanContext> m_VulkanContext;
    };
}
