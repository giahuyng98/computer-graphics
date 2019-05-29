#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H
#include "scene.h"
#include "scene2d.h"
#include <Qt>

class FrameParser
{
public:
    FrameParser(Scene *scene);
    FrameParser(Scene *scene, const QString &fileName);
    bool setInputFile(const QString &fileName);
    QString getOutPut();
    bool nextFrame(bool stopAtEachFrame = false);
    void removeObj(Item *&item);
    void reset();

    void outPutItem(Item *item);
    void outPutTranslation(Item *item, int dx, int dy);
    void outPutRotation(Item *item, int x, int y, int angle);
    void outPutScaling(Item *item, float sx, float sy);
    void outPutReflection(Item *item, int x, int y);
    void outPutDeletion(Item *item);
    void outPutClear();
    void outPutChangeColor(Item *item, const QColor &color);
    void outPutFillColor(Item *item, const QColor &color);
    void outPutAddition();

protected:
    void add();
    void trans();
    void rotate();
    void scale();
    void reflect();
    void doDelete();
    void doClear();
    void changeColor();
    void fillColor();


private:    
    Scene *scene;    
    QString outStream, inStream;
    QTextStream in, out;
    std::map<QString, Item*> objs;
};

#endif // FRAMEPARSER_H
