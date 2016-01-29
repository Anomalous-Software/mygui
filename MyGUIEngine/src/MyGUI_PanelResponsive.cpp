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
		int width = getCoord().width;
		int currentY = 0;
		int totalPadding = (childCount + 1) * padding.width;
		int paddedWidth = width - totalPadding;
		int lowestY = currentY;
		int previousWidgetRight = padding.width;
		int height = getHeight();

		//Always horizontal layout
		int rowStart = 0;
		int columnCount = 0;
		for (int i = 0; i < childCount; ++i)
		{
			Widget* child = getChildAt(i);
			int itemWidth = (int)((float)child->getResponsiveColumnCount() / rowColumns * paddedWidth);
			child->setCoord(previousWidgetRight, currentY, itemWidth, height);
			previousWidgetRight = child->getRight() + padding.width;
		}
	}

	int PanelResponsive::buildRow(int rowStart, int rowEnd, int width, int currentY)
	{
		int count = rowEnd - rowStart;
		int totalPadding = (count + 1) * padding.width;
		int paddedWidth = width - totalPadding;
		int lowestY = currentY;
		//Build previous row
		int previousWidgetRight = padding.width;
		for (int j = rowStart; j < rowEnd; j++)
		{
			Widget* rowChild = getChildAt(j);
			if (rowChild != nullptr)
			{
				int itemWidth = (int)((float)rowChild->getResponsiveColumnCount() / rowColumns * paddedWidth);
				rowChild->setCoord(previousWidgetRight, currentY, itemWidth, rowChild->getHeight());
				previousWidgetRight = rowChild->getRight() + padding.width;
				if (rowChild->getBottom() > lowestY)
				{
					lowestY = rowChild->getBottom();
				}
			}
		}
		return lowestY;
	}

} // namespace MyGUI
