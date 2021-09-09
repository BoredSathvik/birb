#include "Fps.h"

void Fps::OnLevelRender()
{
    frames++;
}

void Fps::OnRender(MinecraftUIRenderContext *ctx)
{

    if (ctx->clientInstance->minecraftGame->canUseKeys)
    {
        std::string text = std::string("FPS: ").append(std::to_string(fps));
        BitmapFont *font = ctx->clientInstance->minecraftGame->Font;
        TextMeasureData measureData = TextMeasureData();
        CaretMeasureData caretData = CaretMeasureData();

        RectangleArea rect = RectangleArea(576, 7, ctx->getLineLength(font, &text, 1) + 7, 15);
        Color color = Color(0, 0, 0, 0.25);
        ctx->fillRectangle(&rect, &color, color.a);

        rect = RectangleArea(580, 10, ctx->getLineLength(font, &text, 1), 15);
        color = Color();
        ctx->drawText(font, &rect, &text, &color, color.a, nullptr, &measureData, &caretData);
        ctx->flushText(0);
    }
}