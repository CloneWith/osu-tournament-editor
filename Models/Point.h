//
// Created by clonewith on 25-3-22.
//

#ifndef POINT_H
#define POINT_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include "../libs/qserializer.h"

class Point : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(int, X)
    QS_FIELD(int, Y)

public:
    Point()
    {
        X = 0;
        Y = 0;
    }

    Point(int x, int y) : X(x), Y(y)
    {
    }
};



#endif //POINT_H
