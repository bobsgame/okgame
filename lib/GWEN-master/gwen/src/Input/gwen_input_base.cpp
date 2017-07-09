//
// GWEN
// Copyright (c) 2013-2015 James Lammlein
// Copyright (c) 2010 Facepunch Studios
//
// This file is part of GWEN.
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Gwen.h"
#include "Gwen/Input/gwen_input_base.h"

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen/Platforms/gwen_platform_base.h"

namespace Gwen
{
namespace Input
{

/// \brief A helper structure to store key data.
struct KeyData
{
    /// \brief Constructor.
    KeyData()
    {
        for (int i = 0; i < Gwen::Key::COUNT; ++i)
        {
            _state[i] = false;
            _next_repeat[i] = 0;
        }

        _target = nullptr;
        _left_mouse_down = false;
        _right_mouse_down = false;
    }

    /// \brief The key state.
    bool _state[Gwen::Key::COUNT];

    /// \brief The time of the next repeat.
    float _next_repeat[Gwen::Key::COUNT];

    /// \brief The target control.
    Controls::Base* _target;

    /// \brief Is the left mouse down?
    bool _left_mouse_down;

    /// \brief Is the right mouse down?
    bool _right_mouse_down;
};

/// \brief The double click speed.
const float DOUBLE_CLICK_SPEED = 0.5f;

/// \brief The maximum number of mouse buttons.
const unsigned MAX_MOUSE_BUTTONS = 5;

/// \brief The key repeat rate.
const float KEY_REPEAT_RATE = 0.03f;

/// \brief The key repeat delay.
const float KEY_REPEAT_DELAY = 0.3f;

/// \brief The last key's data.
static KeyData _key_data;

/// \brief The mouse position.
static Gwen::Point _mouse_position;

/// \brief The last click time.
static float _last_click_time[MAX_MOUSE_BUTTONS];

/// \brief The last click position.
static Gwen::Point _last_click_position;

/// \brief A helper function to update the hovered control.
static void _UpdateHoveredControl(Controls::Base* canvas)
{
    Controls::Base* hovered = nullptr;

    // Calculate the hovered controls.
    std::vector<Controls::Base*> hovered_controls;
    hovered_controls.push_back(canvas->GetControlAt(_mouse_position.x, _mouse_position.y));

    if (!hovered_controls.empty())
    {
        // Try to set the first visible, mouse enabled control as the hovered control.
        for (auto control : hovered_controls)
        {
            if (control->Visible() && control->GetMouseInputEnabled())
            {
                hovered = control;
                break;
            }
        }

        // If the hovered controls are hidden and not mouse enabled...
        if (hovered == nullptr)
        {
            // Set the first control as the hovered control.
            hovered = *hovered_controls.begin();
        }
    }

    if (hovered != HoveredControl)
    {
        if (HoveredControl)
        {
            Controls::Base* old_hovered = HoveredControl;
            HoveredControl = nullptr;
            old_hovered->OnMouseLeave();
        }

        HoveredControl = hovered;
        if (HoveredControl)
        {
            HoveredControl->OnMouseEnter();
        }
    }
}

/// \brief A helper function to find the keyboard focus.
static bool FindKeyboardFocus(Controls::Base* control)
{
    if (!control)
    {
        return false;
    }

    if (control->GetKeyboardInputEnabled())
    {
        for (auto i = control->GetChildren().begin(); i != control->GetChildren().end(); ++i)
        {
            Controls::Base* child = *i;
            if (child == KeyboardFocus)
            {
                return false;
            }
        }

        control->Focus();
        return true;
    }

    return FindKeyboardFocus(control->GetParent());
}

//void Blur()
//{
//    if (KeyboardFocus)
//    {
//        KeyboardFocus->Blur();
//    }
//}

bool IsKeyDown(int key)
{
    return _key_data._state[key];
}

bool IsLeftMouseDown()
{
    return _key_data._left_mouse_down;
}

bool IsRightMouseDown()
{
    return _key_data._right_mouse_down;
}

//bool IsShiftDown()
//{
//    return IsKeyDown(Gwen::Key::SHIFT);
//}
//
//bool IsControlDown()
//{
//    return IsKeyDown(Gwen::Key::CONTROL);
//}

Gwen::Point GetMousePosition()
{
    return _mouse_position;
}

bool HandleAccelerator(Controls::Base* canvas, char character)
{
    // Build the accelerator search string.
    std::wstring accelerator_string;
    if (Gwen::Input::IsControlDown())
    {
        accelerator_string += L"CTRL+";
    }

    if (Gwen::Input::IsShiftDown())
    {
        accelerator_string += L"SHIFT+";
    }

    character = toupper(character);
    accelerator_string += character;

    if (KeyboardFocus && KeyboardFocus->HandleAccelerator(accelerator_string))
    {
        return true;
    }

    if (MouseFocus && MouseFocus->HandleAccelerator(accelerator_string))
    {
        return true;
    }

    if (canvas->HandleAccelerator(accelerator_string))
    {
        return true;
    }

    return false;
}

void OnMouseMoved(Controls::Base* canvas, int x, int y, int delta_x, int delta_y)
{
    _mouse_position.x = x;
    _mouse_position.y = y;

    Gwen::Controls::Base* target = MouseFocus;
    if (target && target->GetCanvas() != canvas)
    {
        target = nullptr;
    }

    if (target && !target->Visible())
    {
        target = nullptr;
    }

    if (target)
    {
        target->OnMouseMoved(x, y, delta_x, delta_y);
    }

    _UpdateHoveredControl(canvas);
}

bool OnMouseClicked(Controls::Base* canvas, int button, bool is_down)
{
    // If we click on a control that isn't a menu, close all the open menus.
    if (is_down && (!HoveredControl || !HoveredControl->IsMenuComponent()))
    {
        canvas->CloseMenus();
    }

    Gwen::Controls::Base* target = MouseFocus;
    if (!target)
    {
        target = HoveredControl;
    }

    if (target && target->GetCanvas() != canvas)
    {
        target = nullptr;
    }

    if (target && !target->Visible())
    {
        target = nullptr;
    }

    if (!target)
    {
        return false;
    }

    // Sanity.
    if (button >= MAX_MOUSE_BUTTONS)
    {
        return false;
    }

    if (button == 0)
    {
        _key_data._left_mouse_down = is_down;
    }
    else if (button == 1)
    {
        _key_data._right_mouse_down = is_down;
    }

    bool is_double_click = false;
    if (is_down &&
        _last_click_position.x == _mouse_position.x &&
        _last_click_position.y == _mouse_position.y &&
        (Gwen::Platform::GetTimeInSeconds() - _last_click_time[button]) < DOUBLE_CLICK_SPEED)
    {
        is_double_click = true;
    }

    if (is_down && !is_double_click)
    {
        _last_click_time[button] = Gwen::Platform::GetTimeInSeconds();
        _last_click_position = _mouse_position;
    }

    if (is_down)
    {
        if (!FindKeyboardFocus(target))
        {
            if (KeyboardFocus)
            {
                KeyboardFocus->Blur();
            }
        }
    }

    switch (button)
    {
    case 0:
        if (is_double_click)
        {
            target->OnMouseDoubleClickLeft(_mouse_position.x, _mouse_position.y);
        }
        else
        {
            target->OnMouseClickLeft(_mouse_position.x, _mouse_position.y, is_down);
        }

        return true;

    case 1:
        if (is_double_click)
        {
            target->OnMouseDoubleClickRight(_mouse_position.x, _mouse_position.y);
        }
        else
        {
            target->OnMouseClickRight(_mouse_position.x, _mouse_position.y, is_down);
        }

        return true;
    }

    return false;
}

bool OnKeyEvent(Controls::Base* canvas, int key, bool is_down)
{
    Gwen::Controls::Base* target = KeyboardFocus;
    if (target && target->GetCanvas() != canvas)
    {
        target = nullptr;
    }

    if (target && !target->Visible())
    {
        target = nullptr;
    }

    if (is_down)
    {
        if (!_key_data._state[key])
        {
            _key_data._state[key] = true;
            _key_data._next_repeat[key] = Gwen::Platform::GetTimeInSeconds() + KEY_REPEAT_DELAY;
            _key_data._target = target;

            if (target)
            {
                return target->OnKeyPress(key);
            }
        }
    }
    else
    {
        if (_key_data._state[key])
        {
            _key_data._state[key] = false;

            if (target)
            {
                return target->OnKeyRelease(key);
            }
        }
    }

    return false;
}

void OnCanvasThink(Controls::Base* canvas)
{
    Gwen::Point mouse_position = Gwen::Input::GetMousePosition();
    Gwen::Input::OnMouseMoved(canvas, mouse_position.x, mouse_position.y, 0, 0);

    if (MouseFocus &&
        (!MouseFocus->Visible() || !MouseFocus->GetMouseInputEnabled()))
    {
        MouseFocus = nullptr;
    }

    if (KeyboardFocus &&
        (!KeyboardFocus->Visible() || !KeyboardFocus->GetKeyboardInputEnabled()))
    {
        KeyboardFocus = nullptr;
    }

    if (!HoveredControl ||
        !HoveredControl->Visible())
    {
        _UpdateHoveredControl(canvas);
    }

    if (!KeyboardFocus)
    {
        return;
    }

    if (KeyboardFocus->GetCanvas() != canvas)
    {
        return;
    }

    // Simulate key repeats.
    float time = Gwen::Platform::GetTimeInSeconds();
    for (int i = 0; i < Gwen::Key::COUNT; ++i)
    {
        if (_key_data._state[i] && _key_data._target != KeyboardFocus)
        {
            _key_data._state[i] = false;
            continue;
        }

        if (_key_data._state[i] && time > _key_data._next_repeat[i])
        {
            _key_data._next_repeat[i] = Gwen::Platform::GetTimeInSeconds() + KEY_REPEAT_RATE;
            if (KeyboardFocus)
            {
                KeyboardFocus->OnKeyPress(i);
            }
        }
    }
}

}; // namespace Input

}; // namespace Gwen
