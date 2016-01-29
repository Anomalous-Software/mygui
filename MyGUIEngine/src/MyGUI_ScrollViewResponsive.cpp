/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MyGUI_Precompiled.h"
#include "MyGUI_ScrollViewResponsive.h"
#include "MyGUI_Gui.h"

namespace MyGUI
{
	ScrollViewResponsive::ScrollViewResponsive()
		:rowColumns(12),
		horizontalMaxSize(Gui::getInstancePtr()->scalePreserve(300)),
		padding(Gui::getInstancePtr()->scalePreserve(2), Gui::getInstancePtr()->scalePreserve(2))
	{
	}

	ScrollViewResponsive::~ScrollViewResponsive()
	{

	}

	void ScrollViewResponsive::setPropertyOverride(const std::string& _key, const std::string& _value)
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
	void ScrollViewResponsive::setSize(const IntSize& _value)
	{
		ScrollView::setSize(_value);
		repositionChildren();
	}
	/** Set widget position and size */
	void ScrollViewResponsive::setCoord(const IntCoord& _value)
	{
		ScrollView::setCoord(_value);
		repositionChildren();
	}

	void ScrollViewResponsive::repositionChildren(bool allowSecondResize)
	{
		int childCount = getChildCount();
		int width = getViewCoord().width;
		int currentY = 0;

		if (width < horizontalMaxSize) //Vertical Layout
		{
			int adjustedWidth = width - (padding.width * 2);
			for (int i = 0; i < childCount; ++i)
			{
				Widget* child = getChildAt(i);
				child->setCoord(padding.width, currentY, adjustedWidth, child->getHeight());
				currentY = child->getBottom() + padding.height;
			}
		}
		else //Horizontal Layout
		{
			int rowStart = 0;
			int columnCount = 0;
			for (int i = 0; i < childCount; ++i)
			{
				Widget* child = getChildAt(i);
				columnCount += child->getResponsiveColumnCount().width;
				if (columnCount > rowColumns)
				{
					//Build previous row
					currentY = buildRow(rowStart, i, width, currentY) + padding.height;
						
					//Start defining new row
					rowStart = i;
					columnCount = child->getResponsiveColumnCount().width;
				}
			}
			//Build any remaining row elements
			currentY = buildRow(rowStart, childCount, width, currentY);
		}

		//Set final scroll view size
		setCanvasSize(width, currentY);

		//Make sure our canvas is large enough, if not resize again.
		if (allowSecondResize && width != getViewCoord().width)
		{
			repositionChildren(false);
		}
	}

	int ScrollViewResponsive::buildRow(int rowStart, int rowEnd, int width, int currentY)
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
			int itemWidth = (int)((float)rowChild->getResponsiveColumnCount().width / rowColumns * paddedWidth);
			rowChild->setCoord(previousWidgetRight, currentY, itemWidth, rowChild->getHeight());
			previousWidgetRight = rowChild->getRight() + padding.width;
			if (rowChild->getBottom() > lowestY)
			{
				lowestY = rowChild->getBottom();
			}
		}
		return lowestY;
	}

} // namespace MyGUI
