#include "controller_creator.h"

std::shared_ptr<base_controller> creator::get_product()
{
    if (!product)
    {
        product = create_product();
    }

    return product;
}

std::shared_ptr<base_controller> controller_creator::create_product()
{
    return std::shared_ptr<base_controller>(new controller());
}
