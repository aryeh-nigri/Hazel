#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
//#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
//		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()  {}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

		// HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.end();)
		{
			(*--it)->OnEvent(e);

			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			auto[x, y] = Input::GetMousePosition();
			HZ_CORE_TRACE("{0}, {1}", x, y);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
