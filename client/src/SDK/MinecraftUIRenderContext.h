#pragma once

#include <string>

struct BitmapFont
{
};

struct RectangleArea
{
    float x1, x2, y1, y2;
    RectangleArea() : RectangleArea(0, 0){};
    RectangleArea(float x, float y) : RectangleArea(x, y, x + 100, y + 100){};
    RectangleArea(float x, float y, float w, float h)
    {
        this->x1 = x;
        this->y1 = y;
        this->x2 = x + w;
        this->y2 = y + h;
    };
};

struct Color
{
    float r, g, b, a;

    Color() : Color(1.0f, 1.0f, 1.0f) {}
    Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
    Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

struct TextMeasureData
{
    float scale;

    TextMeasureData()
    {
        this->scale = 1.0f;
    }
    TextMeasureData(float scale)
    {
        this->scale = scale;
    }
};

struct CaretMeasureData
{
    int a;
    bool b;

    CaretMeasureData() : CaretMeasureData(0xFFFFFFFF, true){};

    CaretMeasureData(int param_1, bool param_2)
    {
        this->a = param_1;
        this->b = param_2;
    };
};

struct MinecraftUIRenderContext
{
public:
    class ClientInstance *clientInstance;

public:
    class ScreenContext *screenContext;

private:
    virtual void vpad_0();

public:
    virtual float getLineLength(class BitmapFont *font, std::string *text, float scale);

private:
    virtual void vpad_2();
    virtual void vpad_3();

public:
    virtual void drawDebugText(RectangleArea *rect, std::string *text, Color *color, float alpha, class TextAlignment *textAlignment, TextMeasureData *textMeasureData, CaretMeasureData *caretMeasureData);
    virtual void drawText(BitmapFont *font, RectangleArea *rect, std::string *text, Color *color, float alpha, class TextAlignment *textAlignment, TextMeasureData *textMeasureData, CaretMeasureData *caretMeasureData);
    virtual void flushText(float lastflush);

private:
    virtual void vpad_7();
    virtual void vpad_8();
    virtual void vpad_9();
    virtual void vpad_10();
    virtual void vpad_11();

public:
    virtual void drawRectangle(RectangleArea *rect, Color *color, float alpha, int lineWidth);
    virtual void fillRectangle(RectangleArea *rect, Color *color, float alpha);
};