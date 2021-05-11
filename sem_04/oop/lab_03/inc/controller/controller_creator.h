#ifndef CONTROLLER_CREATOR_H
#define CONTROLLER_CREATOR_H

#include "base_controller.h"
#include "controller.h"

class creator
{
public:
    virtual ~creator() = default;
    std::shared_ptr<base_controller> get_product();

protected:
    virtual std::shared_ptr<base_controller> create_product() = 0;

private:
    std::shared_ptr<base_controller> product;
};

class controller_creator : public creator
{
protected:
    virtual std::shared_ptr<base_controller> create_product() override;
};

#endif // CONTROLLER_CREATOR_H
