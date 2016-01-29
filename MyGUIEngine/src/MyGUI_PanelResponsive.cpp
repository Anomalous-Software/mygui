/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MyGUI_Precompiled.h"
#include "MyGUI_PanelResponsive.h"
#include "MyGUI_Gui.h"

namespace MyGUI
{
	PanelResponsive::PanelResponsive()
		:rowColumns(12),
		horizontalMaxSize(Gui::getInstancePtr()->scalePreserve(300)),
		padding(Gui::getInstancePtr()->scalePreserve(2), Gui::getInstancePtr()->scalePreserve(2))
	{
	}

	PanelResponsive::~PanelResponsive()
	{

	}

	void PanelResponsive::setPropertyOverride(const std::string& _key, const std::string& _value)
	{

		if (_key == "RowColumns")
			rowColumns = utility::parseValue<int>(_value);

		else if (_key == "HorizontalMaxSize")
			horizontalMaxSize = Gui::getInstancePtr()->scalePreserve(utility::parseValue<int>(_value));

		else if (_key == "Padding")
			padding = Gui::getInstance().scalePreserve(utility::parseValue<IntSize>(_value));

		else
		{
			Base::setPropertyOverride(_key, _value);
			return;
		}

		eventChangeProperty(this, _key, _value);
	}

	/** Set widget size */
	void PanelResponsive::setSize(const IntSize& _value)
	{
		Base::setSize(_value);
		repositionChildren();
	}
	/** Set widget position and size */
	void PanelResponsive::setCoord(const IntCoord& _value)
	{
		Base::setCoord(_value);
		repositionChildren();
	}

	void PanelResponsive::repositionChildren()
	{
		int childCount = getChildCount();
		int width = getWidth();
		int currentY = 0;

		if (width < horizontalMaxSize) //Vertical Layout
		{
			int height = getHeight();
			int paddedWidth = width - padding.width * 2;
			int totalPadding = (childCount + 1) * padding.height;
			int paddedHeight = height - totalPadding;

			for (int i = 0; i < childCount; ++i)
			{
				Widget* child = getChildAt(i);
				int itemHeight = (int)((float)child->getResponsiveColumnCount() / rowColumns * paddedHeight);
				child->setCoord(padding.width, currentY, paddedWidth, itemHeight);
				currentY = child->getBottom() + padding.height;
			}
		}
		else //Horizontal layout
		{
			int totalPadding = (childCount + 1) * padding.width;
			int paddedWidth = width - totalPadding;
			int previousWidgetRight = padding.width;
			int height = getHeight();

			for (int i = 0; i < childCount; ++i)
			{
				Widget* child = getChildAt(i);
				int itemWidth = (int)((float)child->getResponsiveColumnCount() / rowColumns * paddedWidth);
				child->setCoord(previousWidgetRight, currentY, itemWidth, height);
				previousWidgetRight = child->getRight() + padding.width;
			}
		}
		
	}

} // namespace MyGUI
