#include "Application.h"

namespace Yage
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

        m_Renderer = std::unique_ptr<Renderer>(Renderer::Create(m_Window->GetGLFWWindow()));
    }

    Application::~Application()
    {
        
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(TestFunction));
        YAGE_TRACE("{0}", event);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
            m_Renderer->Render();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;

        return true;
    }

    bool Application::TestFunction(WindowResizeEvent& event)
    {
        if(event.GetWidth() == 0 || event.GetHeight() == 0)
        {
            return false;
        }
        m_Renderer->Resize();
        YAGE_TRACE("Renderer has to reset swapchain");
        return true;
    }

}
