#pragma once

#include "forgepch.h"
#include "Forge/Core.h"

namespace
Forge 
{
	enum class
	EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/* BITs are used to associate event types to multiple categories,
	   e.g. Keyboard and Mouse are both Input */
	enum
	EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

	/* Macro to easily define event types 
	   ## is for concatenation, # is for stringification */
	#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
								   virtual EventType getEventType() const override { return getStaticType(); }\
							       virtual const char* getName() const override { return #type; }

	/* Macro to easily define event categories */
	#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class FORGE_API
	Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags()& category;
		}

		//handle events to be able to stop propagation
		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using eventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(
			Event& event
		): event(event) {}

		template<typename T>
		bool dispatch(eventFn<T> func)
		{
			if (event.getEventType() == T::getStaticType())
			{
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}