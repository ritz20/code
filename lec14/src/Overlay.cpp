#include "Overlay.h"

Overlay::Overlay(drawing_ptr over, drawing_ptr under)
        : Drawing{{&*over, &*under}}
        , over_{over}
        , under_{under}
{ }

bool Overlay::contains(posn point) const
{
    return over_->contains(point) || under_->contains(point);
}

graphics::color Overlay::color_at(posn point) const
{
    bool in_over  = over_->get_bbox().contains(point);
    bool in_under = under_->get_bbox().contains(point);

    if (in_over) {
        if (in_under)
            return graphics::overlay(over_->color_at(point),
                                     under_->color_at(point));
        else
            return over_->color_at(point);
    } else {
        if (in_under)
            return under_->color_at(point);
        else
            return graphics::color::transparent;
    }
}
