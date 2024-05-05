#pragma once
#include <memory>

#include "Renderer.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Yage
{
    class Application
    {
    public:
        Application();
        ~Application();

        void OnEvent(Event& event);
        
        void Run();
    private:
        bool OnWindowClose(WindowCloseEvent& event);

        bool TestFunction(WindowResizeEvent& event);
        
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
        bool m_Running = true;
    };
}
