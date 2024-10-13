#include "../main.h"

void CreateButton(Button *ThisButton, Font textFont, int TextFontSize, char *text, int X, int Y, Color TextC, Color TextHLC, Color ButtonC, Color ButtonHLC)  {
    // Default VAR
    ThisButton->ButtonPress = false;
    ThisButton->ButtonHighlightTrue = false;
    ThisButton->TextColor = TextC;
    ThisButton->TextHighlightColor = TextHLC;
    ThisButton->ButtonColor = ButtonC;
    ThisButton->ButtonHighlightColor = ButtonHLC;
    ThisButton->TextFontSize = TextFontSize;

    // Don't forget free this
    ThisButton->Text = (char*)malloc((strlen(text) + 1) * sizeof(char));
    if (ThisButton->Text == NULL) {
        printf("Malloc Porblem In -> CreateButton"); 
        exit(0);
    }
    strcpy(ThisButton->Text, text);
 
    // Default Extra Width and Height
    ThisButton->TextWidth  = MeasureTextEx(textFont, text, ThisButton->TextFontSize, 1).x;
    ThisButton->TextHeight = MeasureTextEx(textFont, text, ThisButton->TextFontSize, 1).y;
    
    ThisButton->ButtonSize   = (Rectangle){X, Y, ThisButton->TextWidth+20, ThisButton->TextHeight+10};
    ThisButton->TextPosition = (Vector2){
        ThisButton->ButtonSize.x+10,
        ThisButton->ButtonSize.y+5
    };
}

void DrawButton(Button *ThisButton, Font TextFont) {
    if (ThisButton->ButtonHighlightTrue) {
        DrawRectangle(
                ThisButton->ButtonSize.x, ThisButton->ButtonSize.y, 
                ThisButton->ButtonSize.width, ThisButton->ButtonSize.height, ThisButton->ButtonHighlightColor
        );
        DrawTextEx(TextFont, ThisButton->Text, ThisButton->TextPosition, ThisButton->TextFontSize, 1, ThisButton->TextHighlightColor);
    } else {
        DrawRectangle(
                ThisButton->ButtonSize.x, ThisButton->ButtonSize.y, 
                ThisButton->ButtonSize.width, ThisButton->ButtonSize.height, ThisButton->ButtonColor
        );
        DrawTextEx(TextFont, ThisButton->Text, ThisButton->TextPosition, ThisButton->TextFontSize, 1, ThisButton->TextColor);
   
    }
}

void PressButton(Button *ThisButton, Vector2 MousePosition) {
    ThisButton->ButtonHighlightTrue = false; ThisButton->ButtonPress = false;
    if (CheckCollisionPointRec(MousePosition, ThisButton->ButtonSize)) {
        ThisButton->ButtonHighlightTrue = true;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            ThisButton->ButtonPress = true;
        }
    }

}

void UnloadButton(Button *ThisButton) {
   if (ThisButton->Text != NULL) {
    printf("INFO: This Button Free Now -> %s | UwU | \n", ThisButton->Text);
    free(ThisButton->Text);
   } else { printf("INFO: Button Text Is NULL"); }
}


