#include <game/SheetLoaderDAT.h>
#include <game/SpriteSheet.h>
#include <game/CompoSprite.h>
#include <game/CompoSpriteSet.h>
#include <io/BundleInputStream.h>
#include <io/ByteArrayInputStream.h>
#include <io/DataInputStream.h>
#include <io/IOException.h>
#include <io/PathName.h>
#include <lang/Math.h>

using namespace io;
using namespace game;
using namespace gr;
using namespace lang;
using namespace math;
using namespace util;

Sprite* getSprite(const std::string& name, const std::map<std::string, P(SpriteSheet)>& sheets) //14-23 | Correct?
{
    for (std::map<std::string, P(SpriteSheet)>::const_iterator it = sheets.begin(); it != sheets.end(); it++) //16 | correct
    {
        Sprite* sprite = it->second->getSprite(name); //18
        if (sprite) //it->second->getSprite(name) == sprite?
            return sprite;
    }
    return 0;
}

static void loadBinarySheetDAT(Context* context, InputStream& in, SpriteSheet& dstSheet, const std::string& filename) //25-90
{
    DataInputStream dis(in); //27

    if (dis.readInt() == 'KA3D') //30 | KA3D binary
    {
        int chunkSize = dis.readInt(); //33
        if (chunkSize > dis.available()) //34
            throwError(IOException(Format("Malformed KA3D file: {0}", in.toString()))); //35

        while (dis.available()) //38
        {
            unsigned int chunkID = dis.readInt(); //40
            unsigned int chunkSize = dis.readInt(); //41 Isn't this better to read after

            if (chunkID == 'SPRT') //43 | Sprite chunk
            {
                int version = dis.readShort(); //47
                if (version == 1)
                {
                    std::string imagePath = dis.readUTF(); //51

                    if (!filename.empty())
                    {
                        PathName parentPath(filename); //55
                        dstSheet.loadImage(context, parentPath.parent().toString());
                    }

                    int spriteCount = dis.readShort(); //61

                    for (int i = 0; i < spriteCount; i++) //64 | Parse images
                    {
                        const std::string& id = dis.readUTF(); //66
                        int x = dis.readShort(); //67
                        int y = dis.readShort(); //68
                        int width = dis.readShort(); //69
                        int height = dis.readShort(); //70
                        int pivotX = dis.readShort(); //71
                        int pivotY = dis.readShort(); //72

                        dstSheet.createSprite(id, x, y, width, height, pivotX, pivotY, Sprite::ROTATION_NONE); //75
                    }
                }

                else
                    dis.skip(chunkSize); //84
            }
        }
    }
}

static void readBinaryCompoDAT(DataInputStream& dis, const std::string sourceDescription, const std::map<std::string, P(SpriteSheet)>& sheetData, CompoSpriteSet& dstSet) //92
{
    unsigned int chunkSize = dis.readInt(); //94
    if (chunkSize > dis.available()) //95
        throwError(IOException(Format("Malformed Composprite file: {0}", sourceDescription))); //96 | Yeah no read failed

    while (dis.available()) //99 | So unused behaviour, you can have multiple COMP chunks in a single file
    {
        unsigned int chunkID = dis.readInt(); //101
        unsigned int chunkSize = dis.readInt(); //102

        if (chunkID == 'COMP') //104 | Check for the chunk ID | Parsing continues...
        {
            int version = dis.readShort(); //108
            if (version > 1)
            {
                int compositeCount = dis.readShort(); //111
                for (int i = 0; i < compositeCount; i++) //112
                {
                    P(CompoSprite) compoSprite; //115

                    const std::string compositeName = dis.readUTF(); //117
                    int spriteCount = dis.readShort(); //118

                    for (int i = 0; i < spriteCount; i++) //120
                    {
                        const std::string name = dis.readUTF(); //122
                        const std::string& compoId = dis.readUTF(); //123
                        Sprite* sprite = getSprite(name, sheetData); //124
                        if (!sprite)
                            throwError(Exception(Format("Sprite \"{0}\" not loaded while loading {1}", name, dis.toString()))); //126

                        float x = dis.readShort(); //128
                        float y = dis.readShort(); //129
                        float scaleX = dis.readFloat(); //130
                        float scaleY = dis.readFloat(); //131
                        float angle = Math::toRadians(dis.readFloat()); //132
                        bool flipX = dis.readBoolean(); //133
                        bool flipY = dis.readBoolean(); //134
                        float2 flip(flipX ? -1.0 : 1.0, flipY ? -1.0 : 1.0); //135

                        compoSprite->addSprite(name, compoId, sprite, float2(x, y), float2(scaleX, scaleY), flip, angle); //137
                    }

                    dstSet.add(compositeName, compoSprite); //149
                }
            }
        }

        else
            dis.skip(chunkSize); //162 | Yeah no read failed
    }
}

static void readOldBinaryCompoDAT(DataInputStream& dis, const std::string sourceDescription, const std::map<std::string, P(SpriteSheet)>& sheetData, CompoSpriteSet& dstSet) //169-235
{
    unsigned int chunkSize = dis.readInt(); //171
    if (chunkSize > dis.available())
        throwError(IOException(Format("Malformed KA3D file: {0}", sourceDescription))); //173

    while (dis.available()) //So unused behaviour, you can have multiple COMP chunks in a single file
    {
        unsigned int chunkID = dis.readInt(); //178
        unsigned int chunkSize = dis.readInt(); //179

        if (chunkID == 'COMP') //Check for the chunk ID
        {
            int version = dis.readShort(); //185, ok so 0 really just acts like 1
            if (version - 1 < 2)
            {
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
                        compoSprite->addSprite(name, x, y, sprite); //205
                    }

                    if (version == 2) //208 | Useless?
                    {
                        int refPointCount = dis.readShort(); //210
                        for (int i = 0; i < refPointCount; i++) //211
                        {
                            dis.readUTF(); //?
                            dis.readShort(); //?
                            dis.readShort(); //?
                        }
                    }

                    dstSet.add(compositeName, compoSprite); //221
                }
            }

            else
                dis.skip(chunkSize); //230 | Yeah no read failed
        }
    }
}

namespace game
{

SpriteSheet* SheetLoaderDAT::loadSheet(Context* context, const std::string& filename) //242-249
{
    SpriteSheet* dstSheet = new SpriteSheet(); //244
    BundleInputStream in(filename); //245

    loadBinarySheetDAT(context, in, *dstSheet, filename); //247
    return dstSheet;
}

SpriteSheet* SheetLoaderDAT::loadSheet(Context* context, InputStream& clipInputStream, InputStream& imageInputstream) //251-258
{
    SpriteSheet* dstSheet = new SpriteSheet(); //253
    dstSheet->loadImage(context, ""); //254

    loadBinarySheetDAT(context, clipInputStream, *dstSheet, ""); //256
    return dstSheet;
}

std::vector<P(SpriteSheet)> SheetLoaderDAT::loadSheets(Context* context, const std::string& filename) //260
{
    std::vector<P(SpriteSheet)> sheets; //262
    sheets.push_back(loadSheet(context, filename));
    return sheets;
}

void SheetLoaderDAT::loadSheetClips(const std::string& filename, SpriteSheet* dstSheet) //267-271
{
    BundleInputStream in(filename, BundleInputStream::READ_BULK); //269
    loadBinarySheetDAT(0, in, *dstSheet, filename);
}

CompoSpriteSet* SheetLoaderDAT::loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData) //273-277
{
    BundleInputStream is(filename); //275
    return loadCompositeSet(is, sheetData);
}

CompoSpriteSet* SheetLoaderDAT::loadCompositeSet(InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData) //279
{
    CompoSpriteSet* dstSet = new CompoSpriteSet; //281

    ByteArrayInputStream bytein(compoInputStream); //283

    std::string sourceDescription = bytein.toString(); //286
    DataInputStream dis(bytein); //287

    unsigned int chunkID = dis.readInt(); //290 | Magic

    if (chunkID == 'RVIO') //New compo
        readBinaryCompoDAT(dis, sourceDescription, sheetData, *dstSet); //295

    else if (chunkID == 'KA3D') //Legacy compo
        readOldBinaryCompoDAT(dis, sourceDescription, sheetData, *dstSet); //301

    else
        throwError(IOException(Format("Malformed Composite Sprite file: {0}", sourceDescription))); //305

    return dstSet;
}

JSON* SheetLoaderDAT::loadCompositeInfo(const std::string& filename) //310 | Blank!
{
    return 0;
}

}