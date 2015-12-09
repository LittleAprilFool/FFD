#include "obj3d.h"

obj3d::obj3d()
{
    rotateX = 45;
    rotateY = 30;
}

void obj3d::process(QString s) {
    QStringList slist = s.split(" ");

    if((slist[0].compare("v") == 0) & slist.size() == 4) {
        QVector3D point = QVector3D(slist[1].toFloat(), slist[2].toFloat(), slist[3].toFloat());
        ori_V.append(point);
        V.append(point);
        return;
    }
    if((slist[0].compare("vn") == 0) & slist.size() == 4) {
        QVector3D point = QVector3D(slist[1].toFloat(), slist[2].toFloat(), slist[3].toFloat());
        VN.append(point);
        return;
    }

    if((slist[0].compare("f") == 0) & slist.size() >= 4) {
        Face f;

        for(int i = 0; i < (slist.size() - 1); i ++){
            point2d A;
            QStringList plist = slist[i+1].split("/");
            A.v = plist[0].toInt() - 1;
            A.vn = plist[2].toInt() - 1;
            f.append(A);
        }

        F.append(f);

        return;
    }
}

void obj3d::reset(){
    for(int i = 0; i < ori_V.size(); i ++)
        V[i] = ori_V[i];
}

void obj3d::clear(){
    F.clear();
    V.clear();
    VN.clear();
    ori_V.clear();
}
