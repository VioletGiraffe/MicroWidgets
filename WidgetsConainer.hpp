#pragma once

#include <tuple/tuple_helpers.hpp>

#include <tuple>

template <class... ListOfWidgetTypes>
struct WidgetsContainer {
	WidgetsContainer() = default;

	template <class... ListOfWidgetTypes>
	constexpr WidgetsContainer(ListOfWidgetTypes&&... widgets) : _widgets(std::forward<ListOfWidgetTypes>(widgets)...) {}

private:
	std::tuple<ListOfWidgetTypes...> _widgets;
};