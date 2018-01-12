#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product();

    QString getId();
    QString getLabel();
    int getQuantity();
    float getWeight();

private:
    QString m_id;
    QString m_label;
    int m_quantity;
    float m_weight;

};

#endif // PRODUCT_H
