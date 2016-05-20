// Example that renders several circles under various transformations.

#include "Background.h"
#include "Circle.h"
#include "Gradient.h"
#include "Opacity.h"
#include "Overlay.h"
#include "Transform.h"

#include "render.h"

#include <cstdlib>

using namespace graphics;

constexpr size_t width{800}, height{600};

int main()
{
    raster raster(width, height);

    auto c1s = circle({300, 225}, 200);
    auto c1  = gradient(c1s, color{1, 1, 0}, color{0, 1, 0, .2}, Circular{});

    auto c2  = opacity(gradient(circle({500, 225}, 200),
                                color{.5, 0, 0}, color::black,
                                Circular{}, Sinusoidal{10, .25}),
                       0.5);

    auto c3  = transform(opacity(gradient(circle({400, 381}, 200),
                                          color{0, 0, 6}, color::white,
                                          Vertical{}), 0.7),
                         affinity::rotation(10)(affinity::dilation(2, .25))
                                 .centered_on(400, 381));

    auto drawing = overlay(c1, overlay(c2, overlay(c3, background(color::black))));

    simple_render(*drawing, raster);

    raster.write_bmp("circles.bmp");
    system("open circles.bmp");
}