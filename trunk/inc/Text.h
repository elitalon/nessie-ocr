///
/// Text.h
///


#if !defined(_TEXT_H)
#define _TEXT_H

#include "Style.h"
#include "FontProportionality.h"
#include "WordRate.h"

class Text
{
private:
	string content;
	Style styles;
	FontProportionality proportionality;
	WordRate wordRates;
public:
	void Text();
	void addCharacter(char character, Style style);
	void removeCharacter(unsigned int character);
	string content();
	void content(string content);
	Style style();
	void style(unsigned int character, Style style);
	unsigned int length();
	WordRate wordRates();
	FontProportionality proportionality();
	void proportionality(FontProportionality proportionality);
};

#endif  //_TEXT_H
