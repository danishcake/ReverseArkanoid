#pragma once
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>


namespace TextAlignment
{
	enum Enum
	{
		TopLeft, Top, TopRight, Left, Centre, Right, BottomLeft, Bottom, BottomRight
	};
}

namespace TextSize
{
	enum Enum
	{
		Normal, Small
	};
}

struct WidgetText
{
private:
	TextAlignment::Enum alignment_;
	TextSize::Enum text_size_;
	std::string text_;
	std::vector<std::string> text_lines_;
	bool autowrap_;
	int line_break_length_;
	int margin_left_;
	int margin_right_;
	int margin_top_;
	int margin_bottom_;

	void LayoutText()
	{
		if(!autowrap_)
		{
			boost::split(text_lines_, text_, boost::is_any_of("\n"));
		} else
		{
			std::vector<std::string> lines;
			boost::split(lines, text_, boost::is_any_of("\n"));
			text_lines_.clear();
			for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				std::vector<std::string> words;
				std::string builder;
				boost::split(words, *it, boost::is_any_of(" "));
				for(std::vector<std::string>::iterator word = words.begin(); word != words.end(); ++word)
				{
					if(builder.length() + word->length() > static_cast<size_t>(line_break_length_))
					{
						text_lines_.push_back(builder);
						builder = *word;
					} else
					{
						if(builder.length() > 0)
							builder = builder + " " + *word;
						else
							builder = *word;
					}
				}
				text_lines_.push_back(builder);
			}
		}
	}

public:
	WidgetText()
	{
		text_=""; 
		alignment_ = TextAlignment::Centre;
		autowrap_ = false; 
		line_break_length_ = 1000;
		margin_left_ = 4;
		margin_right_ = 4;
		margin_top_ = 4;
		margin_bottom_ = 4;
		text_size_ = TextSize::Normal;
	}

	std::string GetText() const {return text_;}
	std::vector<std::string> GetTextLines() const {return text_lines_;}
	void SetText(std::string _text)
	{
		text_ = _text;
		LayoutText();
	}

	void SetTextSize(TextSize::Enum _text_size){text_size_ = _text_size;}
	TextSize::Enum GetTextSize() const {return text_size_;}

	void SetAlignment(TextAlignment::Enum _alignment){alignment_ = _alignment;}
	TextAlignment::Enum GetAlignment() const {return alignment_;}

	int GetMarginLeft() const {return margin_left_;}
	int GetMarginRight() const {return margin_right_;}
	int GetMarginTop() const {return margin_top_;}
	int GetMarginBottom() const {return margin_bottom_;}
	void SetMargins(int _left, int _right, int _top, int _bottom)
	{
		margin_left_ = _left;
		margin_right_ = _right;
		margin_top_ = _top;
		margin_bottom_ = _bottom;
	}

	bool GetAutowrap() const {return autowrap_;}
	void SetAutowrap(bool _autowrap, int _widget_width)
	{
		autowrap_ = _autowrap;
		if(text_size_ == TextSize::Normal)
			line_break_length_ = (_widget_width - margin_left_ - margin_right_) / 16;
		else
			line_break_length_ = (_widget_width - margin_left_ - margin_right_) / 10;
		LayoutText();
	}
};