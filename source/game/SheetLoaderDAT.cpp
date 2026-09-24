#include <game/SheetLoaderDAT.h>
#include <game/SpriteSheet.h>
#include <game/CompoSprite.h>
#include <game/CompoSpriteSet.h>
#include <io/BundleInputStream.h>
#include <io/ByteArrayInputStream.h>
#include <io/DataInputStream.h>
#include <io/IOException.h>
#include <io/PathName.h>

using namespace io;
using namespace game;
using namespace gr;
using namespace lang;
using namespace math;
using namespace util;

Sprite* getSprite(const std::string& name, const std::map<std::string, P(SpriteSheet)>& sheets) //14
{
    for (std::map<std::string, P(SpriteSheet)>::const_iterator it = sheets.begin(); it != sheets.end(); it++) //correct
    {
        Sprite* sprite = it->second->getSprite(name); //= it->second->getSprite(name) //18
        if (sprite) //it->second->getSprite(name) == sprite?
            return it->second->getSprite(name);
    }
    return 0;
}

static void loadBinarySheetDAT(Context* context, InputStream& in, SpriteSheet& dstSheet, const std::string& filename)
{
    DataInputStream dis(in); //27
    if (dis.readInt() != 'KA3D') //KA3D binary
    {
        return;
    }

    int chunkSize = dis.readInt(); //33
    if (chunkSize > dis.available())
        throwError(IOException(Format("Malformed KA3D file: {0}", in.toString()))); //35

    while (dis.available())
    {
        //
        unsigned int chunkID = dis.readInt(); //40
        unsigned int chunkSize = dis.readInt(); //41 Isn't this better to read after
        if (chunkID != 'SPRT') //Sprite chunk
            dis.skip(chunkSize);
        else
        {
            int version = dis.readShort(); //47
            if (version != 1) //Yeah no
                return;

            std::string imagePath = dis.readUTF(); //51

            if (!filename.empty())
            {
                PathName parentPath(filename); //55
                dstSheet.loadImage(context, parentPath.parent().toString());
            }

            //
            //
            int spriteCount = dis.readShort(); //61

            //
            for (int i = 0; i < spriteCount; i++) //64 Parse images
            {
                const std::string& id = dis.readUTF(); //66
                int x = dis.readShort(); //67
                int y = dis.readShort(); //68
                int width = dis.readShort(); //69
                int height = dis.readShort(); //70
                int pivotX = dis.readShort(); //71
                int pivotY = dis.readShort(); //72
                dstSheet.createSprite(id, x, y, width, height, pivotX, pivotY, Sprite::ROTATION_NONE);
            }
        }
    }
}

static void readBinaryCompoDAT(DataInputStream& dis, const std::string sourceDescription, const std::map<std::string, P(SpriteSheet)>& sheetData, CompoSpriteSet& dstSet) //92
{
    unsigned int chunkSize = dis.readInt(); //94

    if (chunkSize > dis.available())
        throwError(IOException(Format("Malformed Composprite file: {0}", sourceDescription)));; //Yeah no read failed

    while (dis.available()) //So unused behaviour, you can have multiple COMP chunks in a single file
    {
        unsigned int chunkID = dis.readInt();
        unsigned int chunkSize = dis.readInt();
        //Parsing continues...
        if (chunkID != 'COMP') //Check for the chunk ID
            dis.skip(chunkSize); //Yeah no read failed
        else
        {
            int version = dis.readShort(); //108 So unused gotcha

            //
            int compositeCount = dis.readShort(); //111
            for (int i = 0; i < compositeCount; i++) //112
            {
                //
                P(CompoSprite) compoSprite = new CompoSprite; //115

                const std::string compositeName = dis.readUTF(); //117
                int spriteCount = dis.readShort(); //118

                for (int i = 0; i < spriteCount; i++) //120
                {
                    const std::string name = dis.readUTF(); //122
                    const std::string& compoId = dis.readUTF(); //123
                    Sprite* sprite = getSprite(name, sheetData); //124
                    if (!sprite)
                        throwError(Exception(Format("Sprite \"{0}\" not loaded while loading {1}", name, dis.toString())));

                    float x = dis.readShort(); //128
                    float y = dis.readShort(); //129
                    float scaleX = dis.readFloat(); //130
                    float scaleY = dis.readFloat(); //131
                    float angle = dis.readFloat(); //132
                    bool flipX = dis.readBoolean(); //133
                    bool flipY = dis.readBoolean(); //134
                    float2 flip(flipX ? -1.0 : 1.0, flipY ? -1.0 : 1.0); //135
                    compoSprite->addSprite(name, compoId, sprite, float2(x, y), float2(scaleX, scaleY), flip, angle);
                }
                dstSet.add(compositeName, compoSprite);
            }
        }
    }
}

static void readOldBinaryCompoDAT(DataInputStream& dis, const std::string sourceDescription, const std::map<std::string, P(SpriteSheet)>& sheetData, CompoSpriteSet& dstSet) //169
{
    unsigned int chunkSize = dis.readInt(); //171

    if (chunkSize > dis.available())
        throwError(IOException(Format("Malformed KA3D file: {0}", sourceDescription)));

    while (dis.available()) //So unused behaviour, you can have multiple COMP chunks in a single file
    {
        unsigned int chunkID = dis.readInt(); //178
        unsigned int chunkSize = dis.readInt(); //179

        if (chunkID != 'COMP') //Check for the chunk ID
            dis.skip(chunkSize); //Yeah no read failed
        else
        {
            int version = dis.readShort(); //185, ok so 0 really just acts like 1
            if (version - 1 < 2)
                return; //Yeah no
            int compositeCount = dis.readShort(); //188
            for (int i = 0; i < compositeCount; i++) //189
            {

                P(CompoSprite) compoSprite; //192

                const std::string& compositeName = dis.readUTF(); //194
                int spriteCount = dis.readShort(); //195

                for (int i = 0; i < spriteCount; i++) //197
                {
                    const std::string name = dis.readUTF(); //199
                    Sprite* sprite = getSprite(name, sheetData); //200
                    if (!sprite)
                        throwError(Exception(Format("Sprite \"{0}\" not loaded while loading {1}", name, dis.toString()))); //202
                    float x = dis.readShort(); //203
                    float y = dis.readShort(); //204
                    compoSprite->addSprite(name, x, y, sprite);
                }

                if (version == 2)
                {
                    int refPointCount = dis.readShort(); //210
                    for (int i = 0; i < refPointCount; i++) //211
                    {
                        dis.readUTF(); //?
                        dis.readShort(); //?
                        dis.readShort(); //?
                    }
                }
                dstSet.add(compositeName, compoSprite);
            }
        }
    }
}

namespace game
{

SpriteSheet* SheetLoaderDAT::loadSheet(Context* context, const std::string& filename) //242
{
    SpriteSheet* dstSheet = new SpriteSheet(); //244
    BundleInputStream in(filename, BundleInputStream::READ_BULK);
    loadBinarySheetDAT(context, in, *dstSheet, filename);
    return dstSheet;
}

SpriteSheet* SheetLoaderDAT::loadSheet(Context* context, InputStream& clipInputStream, InputStream& imageInputstream) //251
{
    SpriteSheet* dstSheet = new SpriteSheet(); //253
    dstSheet->loadImage(context, "");
    loadBinarySheetDAT(context, clipInputStream, *dstSheet, "");
    return dstSheet;
}

std::vector<P(SpriteSheet)> SheetLoaderDAT::loadSheets(Context* context, const std::string& filename) //260
{
    std::vector<P(SpriteSheet)> sheets;

    //?

    //context->createTexture(filename);

    //sheets.push_back();

    return sheets;
}

void SheetLoaderDAT::loadSheetClips(const std::string& filename, SpriteSheet* dstSheet) //267
{
    BundleInputStream in(filename, BundleInputStream::READ_BULK); //269
    loadBinarySheetDAT(0, in, *dstSheet, filename);
}

CompoSpriteSet* SheetLoaderDAT::loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData) //273
{
    BundleInputStream is(filename); //275
    return loadCompositeSet(is, sheetData);
}

CompoSpriteSet* SheetLoaderDAT::loadCompositeSet(InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData) //279
{
    CompoSpriteSet* dstSet = new CompoSpriteSet; //281

    ByteArrayInputStream bytein(compoInputStream); //283

    //
    std::string sourceDescription = bytein.toString(); //286
    DataInputStream dis(bytein); //287

    unsigned int chunkID = dis.readInt(); //Magic

    if (chunkID == 'RVIO') //New compo
    {
        readBinaryCompoDAT(dis, sourceDescription, sheetData, *dstSet);
    }
    else if (chunkID == 'KA3D') //Legacy compo
    {
        readOldBinaryCompoDAT(dis, sourceDescription, sheetData, *dstSet);
    }
    else
        throwError(IOException(Format("Malformed Composite Sprite file: {0}", sourceDescription)));

    return dstSet;
}

JSON* SheetLoaderDAT::loadCompositeInfo(const std::string& filename)
{
    return 0;
}

}