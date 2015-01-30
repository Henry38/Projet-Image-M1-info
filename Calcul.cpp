
#include "Calcul.h"
#include "Convolution.h"
#include "Matrix.h"

/*augmente les contraste de l'image*/
QImage* Calcul::contour(QImage *imgDepart) {

    //return normeDuGradient(imgDepart);

    QImage *imgArrivee = new QImage(*imgDepart);

    Convolution c;
    c.redimensionnerMatrix(3,0);

    c.modifierCaseMatrix(0,1,-1);
    c.modifierCaseMatrix(2,1,-1);
    c.modifierCaseMatrix(1,0,-1);
    c.modifierCaseMatrix(1,2,-1);
    c.modifierCaseMatrix(1,1, 5);
    c.convolution(imgArrivee, false);

    return imgArrivee;
}

/*retourne l'image en niveau de gris*/
QImage* Calcul::imageEnNiveauDeGris(QImage *imgDepart) {
    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), imgDepart->format());

    QRgb pixel;
    int i, j;
    float tmp;
    int height = imgArrivee->height();
    int width = imgArrivee->width();
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            pixel = imgDepart->pixel(i, j);
            tmp = niveauDeGris(pixel);
            imgArrivee->setPixel(i, j, qRgba(tmp, tmp, tmp, qAlpha(pixel)));
        }
    }

    return imgArrivee;
}

/*redimensionnement classique de l'image a la largeur indiquee*/
QImage* Calcul::redimensionnementEnLargeur(QImage *imgDepart, int targetWidth) {
    QImage *imgArrivee = new QImage(targetWidth, imgDepart->height(), QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    int tmpRatio, coef;
    int xImgDepart = 0;
    int yImgDepart = 0;
    QRgb pixel;

    if (targetWidth < imgDepart->width()) {
        // Redimensionnement négatif
        for (int y=0; y<imgArrivee->height(); y++) {
            xImgDepart = 0;
            yImgDepart = y;
            tmpRatio = targetWidth;
            coef = 0;
            for (int x=0; x<imgArrivee->width(); x++) {
                while (tmpRatio <= imgDepart->width()) {
                   pixel = imgArrivee->pixel(x, y);
                   r1 = qRed(pixel);
                   g1 = qGreen(pixel);
                   b1 = qBlue(pixel);
                   pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                   r2 = qRed(pixel) * ((targetWidth - coef) / ((double)imgDepart->width()));
                   g2 = qGreen(pixel) * ((targetWidth - coef) / ((double)imgDepart->width()));
                   b2 = qBlue(pixel) * ((targetWidth - coef) / ((double)imgDepart->width()));
                   imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                   tmpRatio += targetWidth;
                   coef = 0;
                   xImgDepart++;
                }
                coef = imgDepart->width() - (tmpRatio-targetWidth);
                if (coef > 0) {
                    pixel = imgArrivee->pixel(x, y);
                    r1 = qRed(pixel);
                    g1 = qGreen(pixel);
                    b1 = qBlue(pixel);
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * (coef / ((double) imgDepart->width()));
                    g2 = qGreen(pixel) * (coef / ((double) imgDepart->width()));
                    b2 = qBlue(pixel) * (coef / ((double) imgDepart->width()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                }
                tmpRatio -= imgDepart->width();
            }
        }
    } else {
        // Redimensionnement positif
        for (int y=0; y<imgArrivee->height(); y++) {
            xImgDepart = 0;
            yImgDepart = y;
            tmpRatio = targetWidth;
            for (int x=0; x<imgArrivee->width(); x++) {
                if (tmpRatio >= imgDepart->width()) {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    imgArrivee->setPixel(x, y, pixel);
                    tmpRatio -= imgDepart->width();
                } else {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r1 = qRed(pixel) * (tmpRatio / ((double) imgDepart->width()));
                    g1 = qGreen(pixel) * (tmpRatio / ((double) imgDepart->width()));
                    b1 = qBlue(pixel) * (tmpRatio / ((double) imgDepart->width()));
                    xImgDepart++;
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * ((imgDepart->width()-tmpRatio) / ((double) imgDepart->width()));
                    g2 = qGreen(pixel) * ((imgDepart->width()-tmpRatio) / ((double) imgDepart->width()));
                    b2 = qBlue(pixel) * ((imgDepart->width()-tmpRatio) / ((double) imgDepart->width()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                    tmpRatio = targetWidth - (imgDepart->width()-tmpRatio);
                }
            }
        }
    }

    return imgArrivee;
}

/*redimensionnement classique de l'image a la hauteur indiquee*/
QImage* Calcul::redimensionnementEnHauteur(QImage *imgDepart, int targetHeight) {
    QImage *imgArrivee = new QImage(imgDepart->width(), targetHeight, QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    int tmpRatio, coef;
    int xImgDepart = 0;
    int yImgDepart = 0;
    QRgb pixel;

    if (targetHeight < imgDepart->height()) {
        // Redimensionnement négatif
        for (int x=0; x<imgArrivee->width(); x++) {
            xImgDepart = x;
            yImgDepart = 0;
            tmpRatio = targetHeight;
            coef = 0;
            for (int y=0; y<imgArrivee->height(); y++) {
                while (tmpRatio <= imgDepart->height()) {
                   pixel = imgArrivee->pixel(x, y);
                   r1 = qRed(pixel);
                   g1 = qGreen(pixel);
                   b1 = qBlue(pixel);
                   pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                   r2 = qRed(pixel) * (targetHeight - coef) / ((double) imgDepart->height());
                   g2 = qGreen(pixel) * (targetHeight - coef) / ((double) imgDepart->height());
                   b2 = qBlue(pixel) * (targetHeight - coef) / ((double) imgDepart->height());
                   imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                   tmpRatio += targetHeight;
                   coef = 0;
                   yImgDepart++;
                }
                coef = imgDepart->height() - (tmpRatio-targetHeight);
                if (coef > 0) {
                    pixel = imgArrivee->pixel(x, y);
                    r1 = qRed(pixel);
                    g1 = qGreen(pixel);
                    b1 = qBlue(pixel);
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * (coef / ((double) imgDepart->height()));
                    g2 = qGreen(pixel) * (coef / ((double) imgDepart->height()));
                    b2 = qBlue(pixel) * (coef / ((double) imgDepart->height()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                }
                tmpRatio -= imgDepart->height();
            }
        }
    } else {
        // Redimensionnement positif
        for (int x=0; x<imgArrivee->width(); x++) {
            xImgDepart = x;
            yImgDepart = 0;
            tmpRatio = targetHeight;
            for (int y=0; y<imgArrivee->height(); y++) {
                if (tmpRatio >= imgDepart->height()) {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    imgArrivee->setPixel(x, y, pixel);
                    tmpRatio -= imgDepart->height();
                } else {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r1 = qRed(pixel) * (tmpRatio / ((double) imgDepart->height()));
                    g1 = qGreen(pixel) * (tmpRatio / ((double) imgDepart->height()));
                    b1 = qBlue(pixel) * (tmpRatio / ((double) imgDepart->height()));
                    yImgDepart++;
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * ((imgDepart->height()-tmpRatio) / ((double) imgDepart->height()));
                    g2 = qGreen(pixel) * ((imgDepart->height()-tmpRatio) / ((double) imgDepart->height()));
                    b2 = qBlue(pixel) * ((imgDepart->height()-tmpRatio) / ((double) imgDepart->height()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                    tmpRatio = targetHeight - (imgDepart->height()-tmpRatio);
                }
            }
        }
    }

    return imgArrivee;
}

/*retourne au plus les k chemins verticaux trouves sur l'image d'energie*/
QVector<QVector<int>>* Calcul::cheminsOptimaux(QImage *imgEnergie, int iteration) {
    int width = imgEnergie->width();
    int height = imgEnergie->height();

    QVector<QVector<int> > *listPath = new QVector<QVector<int> >(0);

    // Transforme imgEnergie en matrice d'entier
    int **img = new int*[width];
    for (int x = 0; x < width; ++x) {
        img[x]= new int[height];
        for (int y = 0; y < height; ++y) {
            img[x][y] = niveauDeGris(imgEnergie->pixel(x, y));
        }
    }

    // Matrice des poids cumules
    int mSomme[width][height];
    for (int x=0; x<width; x++) {
        mSomme[x][0] = img[x][0];
    }

    // Matrice des pixels parcourus de la derniere ligne
    bool *parcouru = new bool[width];
    for (int x = 0; x < width; ++x) {
        parcouru[x] = false;
    }

    // Matrice des pixels utilises + variable temporaire
    bool **pixelUse = new bool*[width];
    bool **pixelTmp = new bool*[width];
    for (int x = 0; x < width; ++x) {
        pixelUse[x] = new bool[height];
        pixelTmp[x] = new bool[height];
    }

   int power;
    bool g, m, d;
    int index, x;
    float min;
    int n = 0;

    while (listPath->size() < iteration && n < width) {

        // Remplissage de la matrice mSomme en fonction des pixels utilises
        for (int y=1; y<height; y++) {
            for (int x=0; x<width; x++) {
                power = img[x][y];
                mSomme[x][y] = std::numeric_limits<int>::max();
                for (int k=-1; k<=1; k++) {
                    if (x+k >= 0 && x+k < width) {
                        if (power + mSomme[x+k][y-1] < mSomme[x][y]) {
                            mSomme[x][y] = power + mSomme[x+k][y-1];
                        }
                    }
                }
            }
        }

        min = std::numeric_limits<int>::max();
        for (int x=0; x<width; x++) {
            if (mSomme[x][height-1] < min && !parcouru[x]) {
                min = mSomme[x][height-1];
                index = x;
            }
        }

        n++;
        parcouru[index] = true;
        pixelTmp[index][height-1] = true;

       listPath->append(QVector<int>(0));
        bool fail = false;

        int y = height-1;
        while (y > 0 && !fail) {
            listPath->last().insert(0, index);
            x = index;

            pixelTmp[x][y] = true;
            img[x][y] = 999;

            g = (x-1 >= 0
                  && !pixelUse[x-1][y-1]
//                  && ( !(pixelUse[x-1][y] && pixelUse[x][y-1]) )
                );
            m = !pixelUse[x][y-1];
            d = (x+1 < width
                  && !pixelUse[x+1][y-1]
//                  && ( !(pixelUse[x+1][y] && pixelUse[x][y-1]) )
                 );

            if (g && (mSomme[x-1][y-1] < mSomme[x+1][y-1] || !d)
                  && (mSomme[x-1][y-1] < mSomme[x][y-1] || !m)) {
                index += -1;

            } else if (m && (mSomme[x][y-1] <= mSomme[x+1][y-1] || !d)
                  && (mSomme[x][y-1] <= mSomme[x-1][y-1] || !g)) {
                index += 0;

            } else if (d && (mSomme[x+1][y-1] <= mSomme[x-1][y-1] || !g)
                  && (mSomme[x+1][y-1] < mSomme[x][y-1] || !m)) {
                index += 1;

            } else {
                fail = true;
            }
            --y;
        }

        if (fail) {
            for (int x = 0; x < width; ++x) {
                for (int y = 0; y < height; ++y) {
                    if (pixelTmp[x][y] != pixelUse[x][y]) {
                        img[x][y] = niveauDeGris(imgEnergie->pixel(x, y));
                    }
                    pixelTmp[x][y] = pixelUse[x][y];
                }
            }
            listPath->removeLast();
        } else {
            listPath->last().insert(0, index);
            pixelTmp[index][y] = true;
            img[index][y] = 999;
            for (int x = 0; x < width; ++x) {
                for (int y = 0; y < height; ++y) {
                    pixelUse[x][y] = pixelTmp[x][y];
                }
            }
        }
    }

    for (int x = 0; x < width; ++x) {
        delete img[x];
    }
    delete img;
    delete parcouru;
    for (int x = 0; x < width; ++x) {
        delete pixelUse[x];
        delete pixelTmp[x];
    }
    delete pixelUse;
    delete pixelTmp;

    return listPath;
}

/*redimensionnement intelligent de l'image a la largeur indiquee*/
QImage* Calcul::redimensionnementIntellEnLargeur(QImage *imgDepart, int targetWidth) {
    QImage *imgEnergie = normeDuGradient(imgDepart);
    QImage *imgArrivee;

    int iteration = qAbs(targetWidth - imgDepart->width());
    // Coordonnees X des pixels du chemin les moins importants par ordre croissant
    QVector< QVector<int> > *listPath;
    int decalage;

    // Redimensionnement negatif
    if (targetWidth < imgDepart->width()) {

        // Recepuration des chemins de plus faible poids
        listPath = cheminsOptimaux(imgEnergie, iteration);
        imgArrivee = new QImage(imgDepart->width() - listPath->size(), imgDepart->height(), imgDepart->format());
        //imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), imgDepart->format());

        QImage tmp(imgDepart->width(), imgDepart->height(), QImage::Format_ARGB32);
        tmp.fill(Qt::black);
        for (QVector<int> path : *listPath)  {
            for (int y = 0; y < imgDepart->height(); ++y) {
                tmp.setPixel(path.at(y), y, qRgb(255, 255, 255));
            }
        }

        for (int y = 0; y < imgDepart->height(); ++y) {
            decalage = 0;
            for (int x = 0; x < imgDepart->width(); ++x) {
                if (qRed(tmp.pixel(x, y)) == 0) {
                    imgArrivee->setPixel(x-decalage, y, imgDepart->pixel(x, y));
                } else {
                    decalage++;
                    //imgArrivee->setPixel(x-decalage, y, qRgb(255, 0, 0));
                }
            }
        }

        delete listPath;

    // Redimensionnement positif
    } else if (targetWidth > imgDepart->width()) {

        // Recepuration des chemins de plus faible poids
        listPath = cheminsOptimaux(imgEnergie, iteration);
        imgArrivee = new QImage(imgDepart->width() + listPath->size(), imgDepart->height(), imgDepart->format());

        QImage tmp(imgDepart->width(), imgDepart->height(), QImage::Format_ARGB32);
        tmp.fill(Qt::black);
        for (QVector<int> path : *listPath)  {
            for (int y = 0; y < imgDepart->height(); ++y) {
                tmp.setPixel(path.at(y), y, qRgb(255, 255, 255));
            }
        }

        for (int y = 0; y < imgDepart->height(); ++y) {
            decalage = 0;
            for (int x = 0; x < imgDepart->width(); ++x) {
                if (qRed(tmp.pixel(x, y)) == 0) {
                    imgArrivee->setPixel(x+decalage, y, imgDepart->pixel(x, y));
                } else {
                    imgArrivee->setPixel(x+decalage, y, imgDepart->pixel(x, y));
                    imgArrivee->setPixel(x+decalage+1, y, imgDepart->pixel(x, y));
                    decalage++;
                }
            }
        }

        delete listPath;

    } else {

        imgArrivee = new QImage(*imgDepart);

    }

    delete imgEnergie;

    return imgArrivee;
}

/*redimensionnement intelligent de l'image a la hauteur indiquee*/
QImage* Calcul::redimensionnementIntellEnHauteur(QImage *imgDepart, int targetHeight) {
    QImage *imgArrivee;

    QImage *tmp = new QImage(imgDepart->height(), imgDepart->width(), imgDepart->format());
    for (int x = 0; x < imgDepart->width(); ++x) {
        for (int y = 0; y < imgDepart->height(); ++y) {
            tmp->setPixel(y, x, imgDepart->pixel(x, y));
        }
    }
    QImage *imgEnergie = normeDuGradient(tmp);
    delete tmp;

    int iteration = qAbs(targetHeight - imgDepart->height());
    // Coordonnees X des pixels du chemin les moins importants par ordre croissant
    QVector< QVector<int> > *listPath;
    int decalage;

    // Redimensionnement negatif
    if (targetHeight < imgDepart->height()) {

        // Recepuration des chemins de plus faible poids
        listPath = cheminsOptimaux(imgEnergie, iteration);
        imgArrivee = new QImage(imgDepart->width(), imgDepart->height() - listPath->size(), imgDepart->format());
        //imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), imgDepart->format());

        QImage tmp(imgDepart->width(), imgDepart->height(), QImage::Format_ARGB32);
        tmp.fill(Qt::black);
        for (QVector<int> path : *listPath)  {
            for (int x = 0; x < imgDepart->width(); ++x) {
                tmp.setPixel(x, path.at(x), qRgb(255, 255, 255));
            }
        }

        for (int x = 0; x < imgDepart->width(); ++x) {
            decalage = 0;
            for (int y = 0; y < imgDepart->height(); ++y) {
                if (qRed(tmp.pixel(x, y)) == 0) {
                    imgArrivee->setPixel(x, y-decalage, imgDepart->pixel(x, y));
                } else {
                    decalage++;
                    //imgArrivee->setPixel(x, y-decalage, qRgb(255, 0, 0));
                }
            }
        }

        delete listPath;

    // Redimensionnement positif
    } else if (targetHeight > imgDepart->height()) {

        // Recepuration des chemins de plus faible poids
        listPath = cheminsOptimaux(imgEnergie, iteration);
        imgArrivee = new QImage(imgDepart->width(), imgDepart->height() + listPath->size(), imgDepart->format());

        QImage tmp(imgDepart->width(), imgDepart->height(), QImage::Format_ARGB32);
        tmp.fill(Qt::black);
        for (QVector<int> path : *listPath)  {
            for (int x = 0; x < imgDepart->width(); ++x) {
                tmp.setPixel(x, path.at(x), qRgb(255, 255, 255));
            }
        }

        for (int x = 0; x < imgDepart->width(); ++x) {
            decalage = 0;
            for (int y = 0; y < imgDepart->height(); ++y) {
                if (qRed(tmp.pixel(x, y)) == 0) {
                    imgArrivee->setPixel(x, y+decalage, imgDepart->pixel(x, y));
                } else {
                    imgArrivee->setPixel(x, y+decalage, imgDepart->pixel(x, y));
                    imgArrivee->setPixel(x, y+decalage+1, imgDepart->pixel(x, y));
                    decalage++;
                }
            }
        }

        delete listPath;

    } else {

        imgArrivee = new QImage(*imgDepart);

    }

    delete imgEnergie;

    return imgArrivee;
}

/*retourne l'image representant la norme du gradient de l'image*/
QImage* Calcul::normeDuGradient(QImage *imgDepart) {
    QImage *imgGris = imageEnNiveauDeGris(imgDepart);

    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), QImage::Format_ARGB32);
    Convolution c;

    // Filtre 1 de Sobel
    Matrix *Gx = new Matrix(3,0);
    Gx->insert_element(0, 0, -1);
    Gx->insert_element(0, 1, -2);
    Gx->insert_element(0, 2, -1);
    Gx->insert_element(1, 0, 0);
    Gx->insert_element(1, 1, 0);
    Gx->insert_element(1, 2, 0);
    Gx->insert_element(2, 0, 1);
    Gx->insert_element(2, 1, 2);
    Gx->insert_element(2, 2, 1);
    c.setNoyau(Gx);

    int*** tmpGx = c.convolutionToMatrix(imgGris);

    // Filtre 2 de Sobel
    Matrix *Gy = new Matrix(3,0);
    Gy->insert_element(0, 0, -1);
    Gy->insert_element(0, 1, 0);
    Gy->insert_element(0, 2, 1);
    Gy->insert_element(1, 0, -2);
    Gy->insert_element(1, 1, 0);
    Gy->insert_element(1, 2, 2);
    Gy->insert_element(2, 0, -1);
    Gy->insert_element(2, 1, 0);
    Gy->insert_element(2, 2, 1);
    c.setNoyau(Gy);

    int*** tmpGy = c.convolutionToMatrix(imgGris);

    int tmp;
    // Creation de l'image finale
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            tmp = qAbs(tmpGx[y][x][0]) + qAbs(tmpGy[y][x][0]);
            imgArrivee->setPixel(x, y, qRgba(tmp, tmp, tmp, 255));
        }
    }

    delete Gx;
    delete Gy;
    delete imgGris;

    return imgArrivee;
}

QVector<float> Calcul::getYUV(QRgb pixel) {
    QVector<float> yuv;
    float y = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
    float u = 0.492 * (qBlue(pixel) - y);
    float v = 0.877 * (qRed(pixel) - y);
    yuv.append(y);
    yuv.append(u);
    yuv.append(v);
    return yuv;
}

/*retourne le niveau de gris du pixel*/
float Calcul::niveauDeGris(QRgb pixel) {
    return 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
}

void Calcul::recadrer(QImage* img,QPoint* A,QPoint*B){

    if(A->x()<0){
        A->setX(0);
    }

    if(A->y()<0){
        A->setY(0);
    }

    if(B->x()<0){
        B->setX(0);
    }

    if(B->y()<0){
        B->setY(0);
    }

    if(A->x() > img->width()){
      /*on recadre à la limite*/
       A->setX(img->width());
    }

    if(A->y() > img->height()){
      /*on recadre à la limite*/
        A->setY(img->height());
    }

    if(B->x() > img->width()){
      /*on recadre à la limite*/
        B->setX(img->width());
    }

    if(B->y() > img->height()){
      /*on recadre à la limite*/
        B->setY(img->height());
    }

}

QImage* Calcul::rognerImage(QImage* src, QPoint HG, QPoint BD){

    QImage *dest = new QImage(BD.x()-HG.x(),BD.y()-HG.y(),src->format());

    int ydest;
    int ysrc;
    int xdest = 0;
    int xsrc = HG.x();

    while(xsrc < BD.x())
    {
        ydest = 0;
        ysrc = HG.y();
        while(ysrc < BD.y())
        {
            dest->setPixel(xdest,ydest,src->pixel(xsrc,ysrc));
            ydest++;
            ysrc++;
        }
        xdest++;
        xsrc++;
    }
    return dest;
}
