#include "Renderer.h"

namespace Yage
{
    Renderer* Renderer::Create(GLFWwindow* window)
    {
        return new Renderer(window);
    }
    
    Renderer::Renderer(GLFWwindow* window)
    {
        m_VulkanContext = std::unique_ptr<VulkanContext>(VulkanContext::Create(window));
        m_VulkanContext->Init();
    }

    Renderer::~Renderer()
    {
        
    }

    void Renderer::Render()
    {
        m_VulkanContext->DrawFrame();
    }

    void Renderer::Resize()
    {
        m_VulkanContext->RecreateSwapChain();
    }
}
