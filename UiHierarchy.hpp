#pragma once

#include "Widget.h"
#include <tuple/tuple_helpers.hpp>

#include <tuple>

template <class... ListOfScreenTypes>
class UiHierarchy {
public:
	template <size_t index>
	auto& getScreen()
	{
		return std::get<index>(_screens);
	}

	constexpr size_t numScreens() const
	{
		return std::tuple_size<decltype(_screens)>::value;
	}

	size_t currentScreenIndex() const
	{
		return _currentScreenIndex;
	}

	void toNextScreen()
	{
		if (_currentScreenIndex != numScreens() - 1)
		{
			++_currentScreenIndex;
			updateCurrentScreen();
		}
	}

	void toPreviousScreen()
	{
		if (_currentScreenIndex != 0)
		{
			--_currentScreenIndex;
			updateCurrentScreen();
		}
	}

	void toFirstScreen()
	{
		if (_currentScreenIndex != 0)
		{
			_currentScreenIndex = 0;
			updateCurrentScreen();
		}
	}

	void toLastScreen()
	{
		if (_currentScreenIndex != numScreens() - 1)
		{
			_currentScreenIndex = numScreens() - 1;
			updateCurrentScreen();
		}
	}

	void updateCurrentScreen()
	{
		tuple::visit_at(_screens, _currentScreenIndex, ScreenUpdateFunctor());
	}

private: // TODO: replace with [](auto& screen) {screen.update();} as soon as Due platform supports this
	struct ScreenUpdateFunctor {
		template <typename ScreenType>
		void operator()(ScreenType& screen) {
			screen.update();
		}
	};

private:
	std::tuple<ListOfScreenTypes...> _screens;
	size_t _currentScreenIndex = 0;
};