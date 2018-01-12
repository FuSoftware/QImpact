#include "product.h"

Product::Product()
{

}

QString Product::getId()
{
    return this->m_id;
}

QString Product::getLabel()
{
    return this->m_label;
}

int Product::getQuantity()
{
    return this->m_quantity;
}

float Product::getWeight()
{
    return this->m_weight;
}
