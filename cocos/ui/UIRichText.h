/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __UIRICHTEXT_H__
#define __UIRICHTEXT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

class Label;

namespace ui {
    
/**
 *@brief Rich text element base class.
 * It defines the basic common properties for all rich text element.
 */
class CC_GUI_DLL RichElement : public Ref
{
public:
    /**
     *@brief Rich element type.
     */
    enum class Type
    {
        TEXT,
        IMAGE,
        CUSTOM,
        NEWLINE
    };
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichElement(){};
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElement(){};

    
    /**
     * @brief Initialize a rich element with different arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in @see `Color3B`.
     * @param opacity A opacity value in `GLubyte`.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity);
protected:
    Type _type;
    int _tag;
    Color3B _color;
    GLubyte _opacity;
    friend class RichText;
};
    
/**
 *@brief Rich element for displaying text.
 */
class CC_GUI_DLL RichElementText : public RichElement
{
public:
    
    /**
     *@brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichElementText()
    {_type = Type::TEXT;};

    enum {
        ITALICS_FLAG = 1 << 0,
        BOLD_FLAG = 1 << 1,
        UNDERLINE_FLAG = 1 << 2,
        STRIKETHROUGH_FLAG = 1 << 3,
        URL_FLAG = 1 << 4
    };
    
    /**
     *@brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementText(){};
    
    /**
     * @brief Initialize a RichElementText with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param text Content string.
     * @param fontName Content font name.
     * @param fontSize Content font size.
     * @param flags: italics, bold, underline or strikethrough
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize, uint32_t flags, const std::string& url);

    
    /**
     * @brief Create a RichElementText with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param text Content string.
     * @param fontName Content font name.
     * @param fontSize Content font size.
     * @param flags: italics, bold, underline or strikethrough
     * @return RichElementText instance.
     */
    static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text,
                                   const std::string& fontName, float fontSize, uint32_t flags=0, const std::string& url="");
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
    uint32_t _flags;
    std::string _url;
    friend class RichText;
    
};
    
/**
 *@brief Rich element for displaying images.
 */
class CC_GUI_DLL RichElementImage : public RichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     *
     */
    RichElementImage(){_type = Type::IMAGE;};

    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementImage(){};

    
    /**
     * @brief Initialize a RichElementImage with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param filePath A image file name.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);

    
    /**
     * @brief Create a RichElementImage with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param filePath A image file name.
     * @return A RichElementImage instance.
     */
    static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);

    void setWidth(int width);
    void setHeight(int height);
protected:
    std::string _filePath;
    Rect _textureRect;
    int _textureType;
    friend class RichText;
    int _width;
    int _height;
};
    
/**
 *@brief Rich element for displaying custom node type.
 */
class CC_GUI_DLL RichElementCustomNode : public RichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichElementCustomNode(){_type = Type::CUSTOM;};

    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};

    
    /**
     * @brief Initialize a RichElementCustomNode with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param customNode A custom node pointer.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    
    /**
     * @brief Create a RichElementCustomNode with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param customNode A custom node pointer.
     * @return A RichElementCustomNode instance.
     */
    static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
protected:
    Node* _customNode;
    friend class RichText;
};
    
/**
 *@brief Rich element for new line.
 */
class CC_GUI_DLL RichElementNewLine : public RichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     *
     */
    RichElementNewLine(){_type = Type::NEWLINE;};
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementNewLine(){};
    
    /**
     * @brief Create a RichElementNewLine with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @return A RichElementNewLine instance.
     */
    static RichElementNewLine* create(int tag, const Color3B& color, GLubyte opacity);
protected:
    friend class RichText;
};
    
/**
 *@brief A container for displaying various RichElements.
 * We could use it to display texts with images easily.
 */
class CC_GUI_DLL RichText : public Widget
{
public:

    enum WrapMode {
        WRAP_PER_WORD,
        WRAP_PER_CHAR
    };
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichText();
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichText();
    
    /**
     * @brief Create a empty RichText.
     *
     * @return RichText instance.
     */
    static RichText* create();

    /**
     * @brief Create a RichText from an XML
     *
     * @return RichText instance.
     */
    static RichText* createWithXML(const std::string& xml);

    /**
     * @brief Insert a RichElement at a given index.
     *
     * @param element A RichElement type.
     * @param index A given index.
     */
    void insertElement(RichElement* element, int index);
    
    /**
     * @brief Add a RichElement at the end of RichText.
     *
     * @param element A RichElement instance.
     */
    void pushBackElement(RichElement* element);
    
    /**
     * @brief Remove a RichElement at a given index.
     *
     * @param index A integer index value.
     */
    void removeElement(int index);

	/**
	 * @brief remove all richElements
	 */
	void removeAllElements();
    
    /**
     * @brief Remove specific RichElement.
     *
     * @param element A RichElement type.
     */
    void removeElement(RichElement* element);
    
    /**
     * @brief Set vertical space between each RichElement.
     *
     * @param space Point in float.
     */
    void setVerticalSpace(float space);
    
    /**
     * @brief Rearrange all RichElement in the RichText.
     * It's usually called internally.
     */
    void formatText();

    //override functions.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;

	/** @brief sets whether height will change automatically
	 */
	void ignoreHeightAdaptWithSize(bool ignore);
	bool isIgnoreHeightAdaptWithSize();

    /** @brief sets the wrapping mode: WRAP_PER_CHAR or WRAP_PER_WORD
     */
    void setWrapMode(WrapMode wrapMode);

    /** @brief returns the current wrapping mode */
    WrapMode getWrapMode() const;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

    bool initWithXML(const std::string& xml);

protected:
    virtual void adaptRenderers() override;

    virtual void initRenderer() override;
    void pushToContainer(Node* renderer);
    void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B& color, GLubyte opacity, uint32_t flags, const std::string& url="");
    void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity, int width, int height);
    void handleCustomRenderer(Node* renderer);
    void formarRenderers();
    void addNewLine();
    int findSplitPositionForWord(cocos2d::Label* label, const std::string& text);
    int findSplitPositionForChar(cocos2d::Label* label, const std::string& text);

    bool _formatTextDirty;
	bool _ignoreHeight;
    Vector<RichElement*> _richElements;
    std::vector<Vector<Node*>*> _elementRenders;
    float _leftSpaceWidth;
    float _verticalSpace;

    // per word, or per char
    WrapMode _wrapMode;
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIRichText__) */
