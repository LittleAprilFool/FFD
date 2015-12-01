#include "obj3d.h"

obj3d::obj3d()
{

}

void obj3d::process(QString s) {
    QStringList slist = s.split(" ");
    if(slist[0].compare("v") & slist.size() == 4) {
        point3d point;
        point.x = slist[1].toFloat();
        point.y = slist[2].toFloat();
        point.z = slist[3].toFloat();
        V.append(point);
    }
    if(slist[0].compare("vn") & slist.size() == 4) {
        point3d point;
        point.x = slist[1].toFloat();
        point.y = slist[2].toFloat();
        point.z = slist[3].toFloat();
        VN.append(point);
    }
    if(slist[0].compare("f") & slist.size() == 4) {
        face f;

        QStringList plist1 = slist[1].split("/");
        f.p1.v = plist1[0].toInt() - 1;
        f.p1.vn = plist1[2].toInt() - 1;

        QStringList plist2 = slist[2].split("/");
        f.p2.v = plist2[0].toInt() - 1;
        f.p2.vn = plist2[2].toInt() - 1;

        QStringList plist3 = slist[3].split("/");
        f.p3.v = plist3[0].toInt() - 1;
        f.p3.vn = plist3[2].toInt() - 1;

        F.append(f);
    }

    if(slist[0].compare("f") & slist.size() == 5) {
        face f1;
        face f2;

        QStringList plist1 = slist[1].split("/");
        f1.p1.v = plist1[0].toInt() - 1;
        f1.p1.vn = plist1[2].toInt() - 1;
        f2.p1.v = plist1[0].toInt() - 1;
        f2.p1.vn = plist1[2].toInt() - 1;

        QStringList plist2 = slist[2].split("/");
        f1.p2.v = plist2[0].toInt() - 1;
        f1.p2.vn = plist2[2].toInt() - 1;

        QStringList plist3 = slist[3].split("/");
        f1.p3.v = plist3[0].toInt() - 1;
        f1.p3.vn = plist3[2].toInt() - 1;
        f2.p2.v = plist3[0].toInt() - 1;
        f2.p2.vn = plist3[2].toInt() - 1;

        QStringList plist4 = slist[4].split("/");
        f2.p3.v = plist4[0].toInt() - 1;
        f2.p3.vn = plist4[2].toInt() - 1;

        F.append(f1);
        F.append(f2);
    }
}


