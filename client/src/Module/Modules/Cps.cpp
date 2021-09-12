#include "Cps.h"

bool Cps::OnMouse(char button, char pressed, short mX, short mY)
{
    if (button == 1)
    {
        if (pressed)
        {
            lClicks += 1;
        }
    }
    else if (button == 2)
    {
        if (pressed)
        {
            rClicks += 1;
        }
    }
    return false;
}

void Cps::OnRender(MinecraftUIRenderContext *ctx)
{
    if (ctx->clientInst->minecraftGame->canUseKeys)
    {
        unsigned int ldcps = 0;
        unsigned int rdcps = 0;
        for (auto clicks : lcps)
        {
            ldcps += clicks;
        }
        for (auto clicks : rcps)
        {
            rdcps += clicks;
        }
        std::string text = std::string("CPS: ").append(std::to_string(ldcps).append(std::string(" | ").append(std::to_string(rdcps))));
        BitmapFont *font = ctx->clientInst->minecraftGame->Font;

        TextMeasureData measureData = TextMeasureData();
        CaretMeasureData caretData = CaretMeasureData();

        RectangleArea rect = RectangleArea(576, 23, ctx->getLineLength(font, &text, 1) + 7, 15);
        Color color = Color(0, 0, 0, 0.25);
        ctx->fillRectangle(&rect, &color, color.a);

        rect = RectangleArea(580, 26, ctx->getLineLength(font, &text, 1), 1000);
        color = Color();

        ctx->drawText(font, &rect, &text, &color, color.a, nullptr, &measureData, &caretData);
        ctx->flushText(0);
    }
}