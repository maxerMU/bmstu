#include "qt_factory.h"

std::shared_ptr<base_drawer> qt_factory::create_drawer()
{
    return std::shared_ptr<base_drawer>(new qt_drawer(_scene));
}
