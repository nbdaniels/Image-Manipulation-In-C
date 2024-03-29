#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);

    Shrinker s;
    s.SetInput(reader.GetOutput());
    Crop crop;
    crop.SetRegion(300, 1400, 50, 400);
    crop.SetInput(reader.GetOutput());
    
    Transpose t;
    t.SetInput(crop.GetOutput());

    
    Invert i;
    i.SetInput(t.GetOutput());
    
    Color color(50, 1101, 0, 0, 128);
    
    LRConcat lr;
    lr.SetInput(color.GetOutput());
    lr.SetInput2(i.GetOutput());

    lr.GetOutput()->Update();
    s.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(lr.GetOutput());
    writer.Write(argv[2]);

    CheckSum cs;
    cs.SetInput(s.GetOutput());
    cs.OutputCheckSum("image_checksum");
}
