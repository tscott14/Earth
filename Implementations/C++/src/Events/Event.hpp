#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include "Utilities/StringView.hpp"

#define GET_STATIC_EVENT_TYPE(type) \
    static EventTypes GetStaticEventType() { return EventTypes::type; }


enum class EventTypes
{
    WINDOW_CLOSED_EVENT,
    WINDOW_RESIZE_EVENT,
    WINDOW_FOCUS_GAINED_EVENT,
    WINDOW_FOCUS_LOSTED_EVENT,
    WINDOW_MOVED_EVENT,
    KEY_EVENT,
    TEXT_EVENT,
    CURSOR_MOVED_EVENT,
    CURSOR_ENTERED_EVENT,
    CURSOR_EXITED_EVENT,
    MOUSE_BUTTON_EVENT,
    SCROLL_EVENT,
    // APPLICATION_TICK,
    // APPLICATION_UPDATE,
    // APPLICATION_RENDER,
};

enum class EventCategorys
{
    WINDOW_EVENTS = 1 << 1,
    KEYBOARD_EVENTS = 1 << 2,
    MOUSE_EVENTS = 1 << 3,
    APPLICATION_EVENTS = 1 << 4,
};

struct Event
{
    const EventTypes mEventType{};
    const EventCategorys mEventCategory{};
    bool mHandled{};

    Event(EventTypes event_type, EventCategorys event_category)
        : mEventType(event_type),
          mEventCategory(event_category)
    {
    }

    virtual auto ToString() const -> StringView = 0;
};

struct WindowClosedEvent : public Event
{
    WindowClosedEvent()
        : Event(EventTypes::WINDOW_CLOSED_EVENT, EventCategorys::WINDOW_EVENTS)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Closed Event";
    }

    GET_STATIC_EVENT_TYPE(WINDOW_CLOSED_EVENT)
};

struct WindowResizeEvent : public Event
{
    const int mWidth;
    const int mHeight;

    WindowResizeEvent(int width, int height)
        : Event(EventTypes::WINDOW_RESIZE_EVENT, EventCategorys::WINDOW_EVENTS),
          mWidth(width), mHeight(height)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Window Resized Event";
    }

    GET_STATIC_EVENT_TYPE(WINDOW_RESIZE_EVENT)
};

struct WindowFocusGainedEvent : public Event
{
    WindowFocusGainedEvent()
        : Event(EventTypes::WINDOW_FOCUS_GAINED_EVENT, EventCategorys::WINDOW_EVENTS)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Window Focus Gained Event";
    }

    GET_STATIC_EVENT_TYPE(WINDOW_FOCUS_GAINED_EVENT)
};

struct WindowFocusLostEvent : public Event
{
    WindowFocusLostEvent()
        : Event(EventTypes::WINDOW_FOCUS_LOSTED_EVENT, EventCategorys::WINDOW_EVENTS)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Window Focus Losted Event";
    }

    GET_STATIC_EVENT_TYPE(WINDOW_FOCUS_LOSTED_EVENT)
};

struct WindowMovedEvent : public Event
{
    int mX;
    int mY;

    WindowMovedEvent(int x, int y)
        : Event(EventTypes::WINDOW_MOVED_EVENT, EventCategorys::WINDOW_EVENTS),
          mX(x), mY(y)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Window Moved Event";
    }

    GET_STATIC_EVENT_TYPE(WINDOW_MOVED_EVENT)
};

struct KeyEvent : public Event
{
    const int mKey;
    const int mScancode;
    const int mAction;
    const int mMods;

    KeyEvent(int key, int scancode, int action, int mods)
        : Event(EventTypes::KEY_EVENT, EventCategorys::KEYBOARD_EVENTS),
          mKey(key),
          mScancode(scancode),
          mAction(action),
          mMods(mods)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Key Input Event";
    }

    GET_STATIC_EVENT_TYPE(KEY_EVENT)
};

struct TextEvent : public Event
{
    const unsigned int mCodepoint;

    TextEvent(unsigned int codepoint)
        : Event(EventTypes::TEXT_EVENT, EventCategorys::KEYBOARD_EVENTS),
          mCodepoint(codepoint)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Text Input Event";
    }

    GET_STATIC_EVENT_TYPE(TEXT_EVENT)
};

struct CursorMovedEvent : public Event
{
    const float mPosX;
    const float mPosY;
    const float mPosDx;
    const float mPosDy;

    CursorMovedEvent(float x, float y, float dx, float dy)
        : Event(EventTypes::CURSOR_MOVED_EVENT, EventCategorys::MOUSE_EVENTS),
          mPosX(x), mPosY(y),
          mPosDx(dx), mPosDy(dy)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Cursor Moved Event";
    }

    GET_STATIC_EVENT_TYPE(CURSOR_MOVED_EVENT)
};

struct CursorEnteredEvent : public Event
{
    CursorEnteredEvent()
        : Event(EventTypes::CURSOR_ENTERED_EVENT, EventCategorys::MOUSE_EVENTS)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Cursor Entered Window Event";
    }

    GET_STATIC_EVENT_TYPE(CURSOR_ENTERED_EVENT)
};

struct CursorExitedEvent : public Event
{
    CursorExitedEvent()
        : Event(EventTypes::CURSOR_EXITED_EVENT, EventCategorys::MOUSE_EVENTS)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Cursor Left Window Event";
    }

    GET_STATIC_EVENT_TYPE(CURSOR_EXITED_EVENT)
};

struct MouseButtonEvent : public Event
{
    const int mButton;
    const int mAction;
    const int mMods;

    MouseButtonEvent(int btn, int actn, int mods)
        : Event(EventTypes::MOUSE_BUTTON_EVENT, EventCategorys::MOUSE_EVENTS),
          mButton(btn),
          mAction(actn),
          mMods(mods)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Mouse Button Event";
    }

    GET_STATIC_EVENT_TYPE(MOUSE_BUTTON_EVENT)
};

struct ScrollEvent : public Event
{
    const float mOffsetX;
    const float mOffsetY;

    ScrollEvent(float x, float y)
        : Event(EventTypes::SCROLL_EVENT, EventCategorys::MOUSE_EVENTS),
          mOffsetX(x), mOffsetY(y)
    {
    }

    virtual auto ToString() const -> StringView override
    {
        return "Scroll Event";
    }

    GET_STATIC_EVENT_TYPE(SCROLL_EVENT)
};

class EventDispatcher
{
private:
    template <typename T>
    using EventFn = std::function<bool(T &)>;

    Event &mEvent;

public:
    EventDispatcher(Event &event)
        : mEvent(event)
    {
    }

    template <typename T>
    bool Dispatch(EventFn<T> func)
    {
        if (mEvent.mEventType == T::GetStaticEventType())
        {
            mEvent.mHandled = func(*(T *)&mEvent);
            return true;
        }
        return false;
    }
};

#endif