#ifndef UI
#define UI

#include <raylib.h>
typedef struct {
    // Text
    char      *Text;
    Vector2   TextPosition;
    int       TextWidth;
    int       TextHeight;
    Color     TextColor;
    Color     TextHighlightColor;
    int       TextFontSize;

    // Rectangle
    Rectangle ButtonSize;
    Color     ButtonColor;
    Color     ButtonHighlightColor;
    bool      ButtonPress;
    bool      ButtonHighlightTrue;
} Button;

void CreateButton(Button *ThisButton, Font textFont, int TextFontSize, char *text, int X, int Y, Color TextC, Color TextHLC, Color ButtonC, Color ButtonHLC); 
void DrawButton(Button *ThisButton, Font TextFont);
void PressButton(Button *ThisButton, Vector2 MousePosition);
void UnloadButton(Button *ThisButton);


typedef struct {
    char     *Text;
    Color     TextColor;
    Rectangle Window; 
    Color     WindowColor;
} TextBox;


typedef struct {
	Rectangle Slider;
	Color     SliderColor;

} Slider;




#endif
